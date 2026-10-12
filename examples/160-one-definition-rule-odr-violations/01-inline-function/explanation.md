# 160 — One Definition Rule (ODR) violations

## Why the bad code is wrong (`bad.cpp`)

`scale()` is an inline function defined in two translation units with different bodies (`return 2` and `return 3`). The ODR requires that a function defined in more than one translation unit have identical definitions; violating that is ill-formed, no diagnostic required, so neither the compiler nor the linker has to complain, and none does. Which body is used becomes an accident of optimization and link order: with the files linked in the order `bad.cpp bad_b.cpp`, both compilers printed `a_value = 20, b_value = 20` at `-O0` (the linker kept one definition of `scale`) and `a_value = 20, b_value = 30` at `-O2` (each call was inlined from its own translation unit's definition). With the order swapped, `-O0` printed `30, 30` and `-O2` printed `20, 30`.

Neither compiler warns under `-Wall -Wextra` (each sees only one definition), and no tool I ran flags it. A reviewer finds it by searching for the same name defined in several files. Multi-file case: the extra translation units named in the `// also:` header line of `bad.cpp` are compiled and linked with it by `tools/check_examples.py` (see the `extra` key in `footguns.json`).

## The fix (`good.cpp`)

Give each translation unit its own entity: an unnamed namespace (or `static`) gives internal linkage, so the two `scale` functions are different functions (`good.cpp`/`good_b.cpp` print `a_value = 20, b_value = 30` regardless of optimization level), or put the one shared definition in a header so every translation unit sees the same text.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

