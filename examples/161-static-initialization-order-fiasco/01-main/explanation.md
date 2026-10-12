# 161 — Static initialization order fiasco

## Why the bad code is wrong (`bad.cpp`)

`derived` is dynamically initialized from `base`, which is defined in another translation unit with a dynamic initializer (`compute()`). Within one translation unit, order is the order of definition, but across translation units the order of dynamic initialization of non-local variables is unspecified (indeterminately sequenced). Before `base`'s initializer runs, `base` is zero (static zero-initialization), so `derived` becomes 1.

In these builds the outcome followed the order of the files on the command line: with `bad.cpp bad_b.cpp`, both compilers printed `base = 5, derived = 1 (expected 6)` at `-O0`, and g++ also at `-O2`; clang++ at `-O2` printed `derived = 6` for both file orders (I did not investigate why). With `bad_b.cpp bad.cpp`, every combination printed `derived = 6`. Neither compiler warns under `-Wall -Wextra`. Multi-file case: the extra translation units named in the `// also:` header line of `bad.cpp` are compiled and linked with it by `tools/check_examples.py` (see the `extra` key in `footguns.json`).

## The fix (`good.cpp`)

Replace the cross-translation-unit dependency with construct-on-first-use: `base()` returns a function-local static, initialized the first time anyone calls it (and thread-safe since C++11). The fixed program prints `base = 5, derived = 6 (expected 6)`. Alternatives: `constinit` (C++20) for variables that can be constant-initialized, or avoid dynamic initialization of globals.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

