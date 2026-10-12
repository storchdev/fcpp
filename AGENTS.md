# AGENTS.md — building the C++ footgun example catalog

This repo is a catalog of 182 C++ footguns (interview-style "gotchas"). `footguns.json` is the index; `examples/` holds runnable code and the long explanations. Your job is to fill in the examples for entries whose `examples.status` is `"todo"`.

## Files

| Path | Purpose |
| --- | --- |
| `raw.txt` | Original source list. Read-only reference. |
| `footguns.json` | Index of all entries (id, category, title, description, classification, difficulty, `cpp_standard`, `cppreference_urls`, `examples`). |
| `examples/` | One folder per entry, one subfolder per case. |
| `tools/check_examples.py` | Builds and runs every example. Run it before you finish. |

Classification codes: `UB` undefined behavior, `IF` ill-formed/compile failure, `UNS` unspecified/implementation-defined, `LOGIC` well-defined but surprising, `PERF` performance footgun, `CONC` concurrency/memory-model trap.

The code describes the *language rule* involved, not how the compiler reports it. `IF` means the standard makes the program ill-formed, even if one compiler only warns (e.g. g++ warns for non-constant narrowing in braces where clang++ errors). A construct that compiles with only a warning is classified by what the code then does (`UB`, `LOGIC`, ...).

**The entry-level `classification` in `footguns.json` is the primary lesson. Every case also gets its own `classification`**, because cases of one entry often differ (006: one case `LOGIC`, one `IF`). While writing cases, check the entry's code against what the cases actually show; if they disagree, fix the case codes and report any entry-level change (you may now change `classification` on entry or case for this reason, and only this reason).

## Detection

Every case's JSON has a `detection` list: the mechanisms that catch `bad.cpp`, as verified by `tools/check_examples.py` (it fails if a listed mechanism does not fire). Items:

- `error`: `bad.cpp` is ill-formed (`// expect: compile-error`).
- `warning:<g++|clang++>:<-Wflag>`: the compiler emits `[-Wflag]` for `bad.cpp` under `-Wall -Wextra` plus that flag. List the flag per compiler; names differ (`-Wreorder` vs `-Wreorder-ctor`). Flags outside `-Wall -Wextra` such as `-Wconversion` are fine, they just have to be real.
- `sanitizer:<name>`: must equal the `// sanitize:` header.
- `tool:clang-tidy:<check>`: `clang-tidy -checks='-*,<check>'` reports it.
- `none`: nothing tested catches it (alone in the list). Say in `explanation.md` how a reviewer would find it.

List only mechanisms you ran. A warning that covers only part of the bad code (e.g. `-Wmissing-field-initializers` catches missing trailing members but not reordering) is still listed; explain the gap in `explanation.md`.

## Layout

```
examples/NNN-short-slug/
  README.md                 OPTIONAL entry overview (see "When to write a README")
  01-case-name/
    bad.cpp                 the wrong code; compiles and demonstrates the problem
    good.cpp                the corrected C++
    good.rs                 OPTIONAL Rust equivalent
    explanation.md          why bad is bad (long), why good works, Rust notes
    compilers.md            g++ vs clang++ results for bad.cpp (required, see "Writing `compilers.md`")
  02-another-case/
    ...
```

- `NNN` is the zero-padded `id` from `footguns.json`. The slug is ~5 lowercase hyphenated words from the title.
- Case folders are `NN-kebab-name`, numbered from `01`. A single-case entry still uses `01-main/` (or a more descriptive name).
- Every file in a case is optional, but a case needs at least `bad.cpp` + `good.cpp` + `explanation.md` + `compilers.md` unless the footgun is purely a compile error (see "IF entries").
- Never put code in the JSON or in `explanation.md` that isn't also in a file that compiles. The explanation may quote snippets of the files.

## Workflow for each entry

1. Read the entry in `footguns.json` (title, description, classification, `cpp_standard`) and open its `cppreference_urls` for the exact rules. Use the standard's wording; do not guess about UB.
2. Decide how many cases are needed (next section).
3. For each case write `bad.cpp`, `good.cpp`, optional `good.rs`, `explanation.md`, `compilers.md`.
4. Run `python3 -I tools/check_examples.py <NNN>` and fix everything it reports.
5. Update `footguns.json` (see "Updating the JSON"), including each case's `classification` and `detection`.
6. Do not mark an entry done if any of its files fail the checker.

Work in batches (a category at a time) and stop to report; do not try to do all 177 remaining entries in one pass.

## When to use multiple cases

**Default to one case.** Add more only when a single example would leave the reader with a wrong or incomplete mental model. Use more than one case when:

1. **The entry names several distinct mechanisms.** The title or description contains "vs.", "and", or lists variants. Examples: `insert` / `emplace` / `try_emplace` (099) — one case per function; `0`, `NULL`, `nullptr` (008); `reserve()` vs `resize()`.
2. **The rule has exceptions that flip the outcome.** The classic example is temporary lifetime extension (026): extension works for a plain reference binding, but not through a function return, a `new` expression, or a reference member in a constructor. One case for the rule, one per exception that matters.
3. **Behavior depends on the language version or implementation.** Show the old and new behavior as separate cases, with `// std:` set per case (e.g. range-`for` over a temporary: C++20 vs C++23 in 035; argument evaluation order before/after C++17 in 065).
4. **The bug has different failure modes that need different fixes.** E.g. `std::vector` invalidation (092): `push_back` reallocation vs `insert` in the middle vs holding a reference across `emplace_back`. Don't do this if the fix is the same for all of them.
5. **One example would be misleading.** If the simplest demo only "works" by accident (e.g. a data race that always appears fine on x86), add a second case that shows the real hazard (e.g. a hoisted load in a spin loop).
6. **The atomics/memory-model entries (130–138).** Prefer a pair of cases: the *broken* interleaving shown with relaxed ordering, and the version made correct by release/acquire (or seq_cst), because the contrast is the lesson. Remember litmus tests are non-deterministic; see "Non-deterministic bugs".

**Do not** split into multiple cases just to vary syntax, or to pad. If two cases would share the same `explanation.md` argument, merge them. Aim for 1–3 cases per entry; more than 4 is a sign the entry should be argued in a `README.md` instead.

### When to write a README

Add `examples/NNN-slug/README.md` only when there are 2+ cases and the reader needs framing: the one-paragraph rule, a table mapping cases to the exception or variant each covers, and the recommended mental model. Single-case entries don't need one. Keep it short; the depth belongs in each case's `explanation.md`.

## Writing the code

### `bad.cpp`
- Must **compile** (with `-Wall -Wextra` warnings allowed) and demonstrate the problem when run under the right sanitizer. If the footgun is a compile error, see "IF entries".
- First lines, before any `#include`:
  ```cpp
  // std: c++17
  // sanitize: address        <- one of: address | undefined | thread | memory (omit if none applies)
  // One-line statement of what is wrong.
  ```
  - `address`: use-after-free/scope, buffer overflow. Run with `ASAN_OPTIONS=detect_stack_use_after_return=1` (the checker sets it).
  - `undefined`: signed overflow, bad shifts, misaligned access, null deref, etc.
  - `thread`: data races.
  - `memory`: reading uninitialized values. Uses clang; AddressSanitizer cannot see these.
  - For `PERF`/`LOGIC` entries with no sanitizer, the checker only requires that the bad code builds and runs; make the bad behavior visible in the program's output instead.
- Keep it small (typically 15–40 lines). One idea per file. Comment the exact line(s) where the problem occurs, briefly; the long explanation goes in `explanation.md`.
- It should look plausible, like code a reasonable person would write, not a contrived strawman.

### `good.cpp`
- Compiles clean with `-Wall -Wextra` and exits 0. Use the minimum standard needed; set `// std: c++NN`.
- Show the idiomatic fix, not merely a workaround. If there are several valid fixes, show the best one in code and mention the others in `explanation.md`.

### `good.rs`
- Include it when Rust has a genuine contrast: the bug is impossible or a compile error (borrow checker, definite initialization, `Send`/`Sync`, no UB in safe arithmetic), or Rust forces an explicit choice (`checked_add`, `Ordering`).
- Skip it when Rust has no meaningful analogue (ADL, hidden friends, ODR, SFINAE, C++ ABI issues). Don't force it, but the `## Rust (no `good.rs`)` section of `explanation.md` still exists: put the short, useful sentence there ("Rust has no ADL; method resolution is explicit via traits").
- It must compile with `rustc --edition 2021` as a single file with no dependencies and exit 0. Show the rejected code as a commented-out block with the actual error code (e.g. `E0515`) if the point is that the compiler stops you.
- Prefer safe Rust. If the contrast is "this needs `unsafe`", show the unsafe block and explain the invariants.

### IF entries (compile-time failures)
For entries classified `IF`, the bad code intentionally does not compile, which breaks the checker's assumption. Handle it by:
- Putting the failing code in `bad.cpp` with a header line `// expect: compile-error` and a comment giving the compiler's actual error text.
- Extending `tools/check_examples.py` the first time you need it so that `// expect: compile-error` means "compilation must fail", and then confirm the other examples still pass. Keep the change small and mention it in your report.

### Non-deterministic bugs
Data races, memory-order, and reclamation bugs may not reproduce on every run. Rules:
- The bad code must be *detectable* under its sanitizer reliably (TSan for races). Don't claim a specific wrong output unless you have seen it; otherwise say "may print X".
- Don't rely on timing sleeps to force an interleaving in the good code; good code must be correct under any interleaving.
- Never claim hardware behavior (reordering on x86 vs ARM) you haven't verified; attribute to the standard ("permitted by the memory model") instead.

## Never assume: ask the compilers

Every factual claim in an `explanation.md`, a code comment, a README or the JSON must come from something you ran in this session, not from memory or from what the standard "should" imply. Memory has already been wrong here: `-Wzero-as-null-pointer-constant` does not flag `NULL`, g++ accepts a conversion clang++ calls ambiguous, and g++ only warns on non-constant narrowing where clang++ errors.

- Compile every snippet you describe with **both** `g++` and `clang++` (and `rustc` for Rust claims), at the stated `-std=` and optimization level, and read the actual output. Quote diagnostic text as printed, with the compiler version.
- Warning and error claims: run the compiler with the exact flags. "No warning under `-Wall -Wextra`" is only true if you saw none. Check optimization-dependent warnings (`-Wuninitialized`, `-Wmaybe-uninitialized`) at the level the checker uses.
- Claims about a type, overload or value: prove it with `static_assert`, `decltype`, or printed output inside a scratch program, not by reasoning.
- Claims about tools (clang-tidy checks, sanitizers): run the tool and see it report.
- If the two compilers disagree, say so and name both results. If you could not verify a claim, delete it or write "not verified"; never present it as fact.
- Scratch programs for these checks go in the scratchpad, not the repo. If the check is worth keeping, turn it into a `static_assert` in the case's `bad.cpp`/`good.cpp` or a `detection` item so the checker keeps verifying it.

## Writing `explanation.md`

Every `explanation.md` has exactly this skeleton and nothing else; only the title line and the section bodies differ between cases. `check_examples.py` fails any deviation. Use these sections, in order. Keep the bad-code section the longest (typically 2–5 paragraphs). Do not oversimplify; explain the actual standard rule and the actual failure mechanism.

```markdown
# NNN — Title            (for multi-case entries: "NNN.NN — Title: case name")

## Why the bad code is wrong (`bad.cpp`)
- The rule in the standard, stated precisely (cite the construct, not just "UB").
- The exact mechanism: what the compiler/hardware/runtime does, and why it often *appears* to work.
- How it shows up in real code and why reviewers miss it.
- How to detect it (sanitizer, warning flag, tool), with the flag name.

## The fix (`good.cpp`)
- What changed and why it is correct; alternatives and their tradeoffs.

## Rust (`good.rs`)       <- heading is `## Rust (no `good.rs`)` when the case has no good.rs; the section is never omitted
- With good.rs: what Rust does differently and the specific mechanism (borrow checker, types, explicit API).
- Without good.rs: one or two sentences on why there is no analogue (verified with rustc if it states a Rust fact), or "No Rust equivalent is provided for this case."
```

Accuracy rules:
- **Verify claims by running them** (see "Never assume"). If you write "prints 0 at -O2", compile with that flag and check. Compilers differ (GCC vs clang) and a wrong claim here is worse than no claim; state the compiler and flags you observed.
- Distinguish **undefined**, **unspecified**, **implementation-defined**, **erroneous** (C++26), and **ill-formed, no diagnostic required**. Don't call something UB if it isn't (for example: exceptions escaping a `noexcept` function or a destructor call `std::terminate`, which is defined).
- State the standard version in which behavior changed, and keep `cpp_standard` in the JSON as the version that *introduced the relevant feature* (not the version that fixed the problem).
- Prefer cppreference-style names for things; link nothing in the explanation that isn't already in `cppreference_urls` unless you checked it resolves.

## Writing `compilers.md`

Every case with a `bad.cpp` has a `compilers.md` beside `explanation.md`. It is kept separate so a UI can show it as its own tab and so the explanation stays about the language rule. It records what the two compilers did with `bad.cpp`; the cause belongs in `explanation.md`.

```markdown
# NNN — Title: compiler comparison        (same title line as explanation.md, plus ": compiler comparison")

**g++ vs clang++ (g++ X.Y.Z, clang++ X.Y.Z, `-std=... -Wall -Wextra`, sanitizer flags, `-O0` and `-O2`).** One or two sentences, or a table.
```

- Compile and run `bad.cpp` with both compilers, at `-O0` and `-O2` (and at the checker's `-O1` for sanitizer runs), and record what each did: warnings (with the flag), errors (with the text), sanitizer reports (with the kind), and program output.
- If they behave identically, say so with the levels tried ("No difference: neither compiler warns, and both print ... at `-O0` and `-O2`"). Never leave a compiler out.
- If they differ, use a table with `| | g++ | clang++ |` and one row per observation (Warnings, No sanitizer at each level, each sanitizer). Record sanitizer gaps (g++ has no MemorySanitizer) and any `detection` item that exists for only one compiler.
- Garbage values vary per run, so write "garbage" unless you are quoting one specific run.
- `explanation.md` may refer to `compilers.md` ("see `compilers.md`") but must not repeat its tables. Claims in `compilers.md` follow the same "Never assume" rule: nothing that was not run this session.
- The checker (`check_examples.py`) fails a case with no `compilers.md`, one that does not name both `g++` and `clang++`, or one without the `**g++ vs clang++` paragraph. It cannot check that the content is true; that is still on you.

## Updating the JSON

Each entry's `examples` field looks like:

```json
"examples": {
  "status": "done",                       // "todo" | "done"
  "dir": "examples/026-temporary-lifetime-extension",
  "readme": "examples/026-temporary-lifetime-extension/README.md",   // or null
  "cases": [
    {
      "name": "function-return",          // folder name without the NN- prefix
      "classification": "UB",             // this case's code (see Classification codes)
      "detection": ["sanitizer:address", "warning:g++:-Wreturn-local-addr"],   // see "Detection"
      "dir": "examples/026-.../01-function-return",
      "files": {
        "bad_cpp": ".../bad.cpp",
        "good_cpp": ".../good.cpp",
        "good_rust": ".../good.rs",        // omit keys for files that don't exist
        "explanation": ".../explanation.md",
        "compilers": ".../compilers.md"
      }
    }
  ]
}
```

Paths are relative to the repo root. Only include `files` keys for files that exist. Set `status` to `"done"` only after `tools/check_examples.py <NNN>` passes. Do not edit any other field in `footguns.json` without being asked (case and entry `classification` excepted, see above); if you believe a difficulty, standard number, or URL is wrong, report it instead of silently changing it.

Update with a small script (`python3 -I`) rather than hand-editing the 182-entry file, then confirm the file still parses and ids are intact (1–182).

## Tooling and environment

- Compilers: `g++` and `clang++` (needed for MemorySanitizer), `rustc`. All examples are single files.
- Check one entry: `python3 -I tools/check_examples.py 026`. Check everything: `python3 -I tools/check_examples.py`.
- Put scratch files in the session scratchpad, not in the repo.
- The cppreference URLs were all verified to resolve (`/w/cpp/...` redirects to `/cpp/...`). If you add one, check it with `curl -sL -o /dev/null -w '%{http_code}'`, one request at a time with a 1-second delay.

## Definition of done for an entry

- [ ] Case count justified by the "when to use multiple cases" rules.
- [ ] Each case has `bad.cpp`, `good.cpp`, `explanation.md`, `compilers.md`; `good.rs` only where it adds something.
- [ ] `tools/check_examples.py <NNN>` passes (good builds and exits 0; bad is flagged or, for IF entries, fails to compile as expected).
- [ ] Each `compilers.md` covers both g++ and clang++ at `-O0` and `-O2`, and every statement in it was run this session.
- [ ] Every factual claim about compiler output, flags, warnings, tools, or standard versions was run on g++ and clang++ this session (see "Never assume") or cited; anything unverified was removed.
- [ ] Each case has `classification` and `detection` in `footguns.json`, and the checker verifies `detection`.
- [ ] `footguns.json` updated, still valid, ids 1–182 intact.
