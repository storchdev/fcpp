#!/usr/bin/env python3
"""Build and run every example under examples/.

Layout: examples/NNN-slug/NN-case/{bad.cpp,good.cpp,good.rs,explanation.md}; each case is checked
independently and any file may be absent. good.cpp / good.rs must compile cleanly and exit 0.
bad.cpp must compile; when run under its declared sanitizer it is expected to be flagged
(non-zero exit, or sanitizer output). A header line `// sanitize: address|undefined|thread|memory`
selects the sanitizer; `// std: c++NN` selects the standard. `// expect: compile-error` means bad.cpp
must fail to compile. Without a sanitizer, bad.cpp only has to build and run.
"""
import json, re, subprocess, sys, tempfile, os
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent / "examples"
ENV = {**os.environ, "ASAN_OPTIONS": "detect_stack_use_after_return=1",
       "UBSAN_OPTIONS": "print_stacktrace=0"}

def header(path, key, default):
    for line in path.read_text().splitlines()[:10]:
        m = re.match(rf"//\s*{key}:\s*(\S+)", line)
        if m: return m.group(1)
    return default

def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, timeout=60, env=ENV, **kw)

def cpp(src, out, std, san=None, optimize="-O1"):
    cxx = "clang++" if san == "memory" else "g++"
    cmd = [cxx, f"-std={std}", "-Wall", "-Wextra", optimize, "-g", "-pthread", str(src), "-o", str(out)]
    if san: cmd.insert(1, f"-fsanitize={san}")
    if san == "memory": cmd.insert(2, "-fsanitize-memory-track-origins")
    return run(cmd)

def load_detection():
    """Map case directory (relative to repo root) -> detection list from footguns.json."""
    idx = json.loads((ROOT.parent / "footguns.json").read_text())
    return {c["dir"]: c.get("detection") for e in idx for c in e["examples"].get("cases", [])}

def check_detection(items, bad, std, san, exp, tmp):
    """Verify each claimed detection mechanism actually fires on bad.cpp. Returns list of problems."""
    problems = []
    if items == ["none"]: return problems
    for it in items:
        kind, _, rest = it.partition(":")
        if kind == "error":
            if exp != "compile-error": problems.append(f"{it}: bad.cpp has no `// expect: compile-error`")
        elif kind == "sanitizer":
            if rest != san: problems.append(f"{it}: header says sanitize={san}")
        elif kind == "warning":
            cxx, _, flag = rest.partition(":")
            r = run([cxx, f"-std={std}", "-Wall", "-Wextra", flag, "-c", "-o", "/dev/null", "-pthread", str(bad)])
            if f"[{flag}]" not in r.stderr: problems.append(f"{it}: {cxx} did not emit [{flag}]")
        elif kind == "tool":
            tool, _, check = rest.partition(":")
            if tool != "clang-tidy": problems.append(f"{it}: unknown tool"); continue
            r = run(["clang-tidy", f"-checks=-*,{check}", str(bad), "--", f"-std={std}"])
            if f"[{check}]" not in r.stdout: problems.append(f"{it}: clang-tidy did not report {check}")
        else:
            problems.append(f"{it}: unknown detection kind")
    return problems

def lint_explanation(d):
    """explanation.md has a fixed skeleton: title, Why wrong, The fix, Rust (always last, heading depends on good.rs)."""
    ex = d / "explanation.md"
    if not (d / "bad.cpp").exists(): return []
    if not ex.exists(): return ["explanation.md is missing"]
    heads = [l for l in ex.read_text().splitlines() if l.startswith("#")]
    num = d.parent.name[:3]
    multi = sum(1 for c in d.parent.iterdir() if c.is_dir()) > 1
    title = rf"# {num}\.{d.name[:2]} — \S" if multi else rf"# {num} — \S"
    rust = "## Rust (`good.rs`)" if (d / "good.rs").exists() else "## Rust (no `good.rs`)"
    want = ["## Why the bad code is wrong (`bad.cpp`)", "## The fix (`good.cpp`)", rust]
    probs = []
    if not heads or not re.match(title, heads[0]): probs.append(f"first line must match `{title}`")
    if heads[1:] != want: probs.append(f"headings must be exactly {want}, found {heads[1:]}")
    return probs

def lint_compilers(d):
    """Every case needs compilers.md: how g++ and clang++ compare, starting with the labelled paragraph."""
    if not (d / "bad.cpp").exists(): return []
    cm = d / "compilers.md"
    if not cm.exists(): return ["compilers.md is missing (see AGENTS.md)"]
    text, probs = cm.read_text(), []
    if "g++" not in text or "clang++" not in text:
        probs.append("compilers.md must name both g++ and clang++")
    if not re.search(r"^\*\*g\+\+ vs clang\+\+", text, re.M):
        probs.append("compilers.md is missing the `**g++ vs clang++ (versions, flags).**` paragraph")
    return probs

def main():
    detection = load_detection()
    only = sys.argv[1:]
    failures = 0
    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        cases = sorted(c for e in ROOT.iterdir() if e.is_dir() for c in e.iterdir() if c.is_dir())
        for d in cases:
            if only and not any(d.parent.name.startswith(o) for o in only): continue
            print(f"{d.parent.name}/{d.name}")
            good, bad, rs = d / "good.cpp", d / "bad.cpp", d / "good.rs"
            if good.exists():
                r = cpp(good, tmp / "g", header(good, "std", "c++20"))
                ok = r.returncode == 0 and run([tmp / "g"]).returncode == 0
                if r.returncode: print(r.stderr[:600])
                print(f"  good.cpp  {'ok' if ok else 'FAIL'}"); failures += not ok
            if bad.exists():
                san = header(bad, "sanitize", None)
                r = cpp(bad, tmp / "b", header(bad, "std", "c++20"), san)
                if header(bad, "expect", None) == "compile-error":
                    ok = r.returncode != 0
                    print(f"  bad.cpp   {'fails to compile as expected' if ok else 'FAIL (compiled, but should not)'}")
                    failures += not ok
                elif r.returncode:
                    print(r.stderr[:600]); print("  bad.cpp   FAIL (does not compile)"); failures += 1
                else:
                    r = run([tmp / "b"])
                    if san is None:  # LOGIC/PERF: bad code only has to build and run; the behavior is in its output
                        print("  bad.cpp   builds and runs (no sanitizer)")
                    else:
                        flagged = r.returncode != 0 or "runtime error" in r.stderr or "Sanitizer" in r.stderr
                        print(f"  bad.cpp   {'flagged by ' + san if flagged else 'NOT flagged by ' + str(san)}")
                        failures += not flagged
            if bad.exists():
                items = detection.get(str(d.relative_to(ROOT.parent)))
                if items is None:
                    print("  detection not recorded in footguns.json (skipped)")
                else:
                    probs = check_detection(items, bad, header(bad, "std", "c++20"), header(bad, "sanitize", None),
                                            header(bad, "expect", None), tmp)
                    for p in probs: print("  detection FAIL:", p)
                    if not probs: print(f"  detection ok ({', '.join(items)})")
                    failures += bool(probs)
            for prob in lint_explanation(d): print("  explanation.md FAIL:", prob); failures += 1
            for prob in lint_compilers(d): print("  compilers.md FAIL:", prob); failures += 1
            if rs.exists():
                r = run(["rustc", "--edition", "2021", "-O", "-o", str(tmp / "r"), str(rs)])
                ok = r.returncode == 0 and run([tmp / "r"]).returncode == 0
                if r.returncode: print(r.stderr[:600])
                print(f"  good.rs   {'ok' if ok else 'FAIL'}"); failures += not ok
    sys.exit(1 if failures else 0)

main()
