#!/usr/bin/env python3
"""Build and run every example under examples/.

Layout: examples/NNN-slug/NN-case/{bad.cpp,good.cpp,good.rs,explanation.md}; each case is checked
independently and any file may be absent. good.cpp / good.rs must compile cleanly and exit 0.
bad.cpp must compile; when run under its declared sanitizer it is expected to be flagged
(non-zero exit, or sanitizer output). A header line `// sanitize: address|undefined|thread|memory`
selects the sanitizer; `// std: c++NN` selects the standard.
"""
import re, subprocess, sys, tempfile, os
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

def main():
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
                if r.returncode:
                    print(r.stderr[:600]); print("  bad.cpp   FAIL (does not compile)"); failures += 1
                else:
                    r = run([tmp / "b"])
                    flagged = r.returncode != 0 or "runtime error" in r.stderr or "Sanitizer" in r.stderr
                    print(f"  bad.cpp   {'flagged by ' + san if flagged else 'NOT flagged by ' + str(san)}")
                    failures += not flagged
            if rs.exists():
                r = run(["rustc", "--edition", "2021", "-O", "-o", str(tmp / "r"), str(rs)])
                ok = r.returncode == 0 and run([tmp / "r"]).returncode == 0
                if r.returncode: print(r.stderr[:600])
                print(f"  good.rs   {'ok' if ok else 'FAIL'}"); failures += not ok
    sys.exit(1 if failures else 0)

main()
