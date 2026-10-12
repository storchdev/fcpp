# 120.02 — Template instantiation across translation units: definition not visible

## Why the bad code is wrong (`bad.cpp`)

`Box<int>::get()` is declared but never defined in this translation unit, so `b.get()` cannot be instantiated here and the symbol is left for the linker, which finds nothing: both link steps fail with `undefined reference to ‘Box<int>::get() const’`. In real code the definition sits in a `.cpp`; another translation unit would have to explicitly instantiate it (`template struct Box<int>;`) for the link to succeed (a single-file test with that explicit instantiation linked and printed `3` on both compilers).

The compile step passes (it succeeds with `-c`), so the failure appears only at link time, far from the cause. Detection is the failed build (the `// expect: compile-error` header means the build must fail; here the failure comes from the linker, not the compiler).

## The fix (`good.cpp`)

Put the template's definition where it is used (usually the header), as in the good program, or explicitly instantiate the used specializations in one translation unit. The fixed program prints `3`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

