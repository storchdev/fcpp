# 165.02 — Header-defined globals and linkage: static copies

## Why the bad code is wrong (`bad.cpp`)

A namespace-scope `static` variable has internal linkage, so each translation unit gets its own `counter`. `bump()` in `bad_b.cpp` increments its own copy, and `main` in `bad.cpp` reads another, so the program printed `counter = 0 (expected 1)` with both compilers at `-O0` and `-O2`. The same holds for a namespace-scope `const` variable (internal linkage by default). It is well-defined and links without errors or warnings under `-Wall -Wextra`, which is why it survives review. Multi-file case: the extra translation units named in the `// also:` header line of `bad.cpp` are compiled and linked with it by `tools/check_examples.py` (see the `extra` key in `footguns.json`).

## The fix (`good.cpp`)

Use a C++17 `inline` variable so there is a single object (`good_shared.h`). The fixed program prints `counter = 1 (expected 1)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

