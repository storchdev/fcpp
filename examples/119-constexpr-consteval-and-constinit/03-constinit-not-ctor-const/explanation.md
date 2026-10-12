# 119.03 — `constexpr`, `consteval`, and `constinit`: constinit initializer

## Why the bad code is wrong (`bad.cpp`)

`constinit` asserts that a variable with static or thread storage duration is constant-initialized, which avoids the static initialization order problem. `runtime_value()` is not `constexpr`, so the initializer is not a constant expression and the declaration is ill-formed. g++ "‘constinit’ variable ‘g’ does not have a constant initializer", clang++ "variable does not have a constant initializer".

`constinit` does not make the variable `const`: the good program modifies `g` at run time and prints `43`. Detection is the compile error.

## The fix (`good.cpp`)

Initialize with a `constexpr` function or a literal. The fixed program prints `43`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

