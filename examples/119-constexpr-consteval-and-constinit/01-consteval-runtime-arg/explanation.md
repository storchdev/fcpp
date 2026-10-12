# 119.01 — `constexpr`, `consteval`, and `constinit`: consteval with a runtime argument

## Why the bad code is wrong (`bad.cpp`)

A `consteval` function is an immediate function: every call must produce a constant expression. `n` is an ordinary `int` variable, so `square(n)` is not a constant expression and the program is ill-formed. g++ "call to consteval function ‘square(n)’ is not a constant expression", clang++ "call to consteval function 'square' is not a constant expression".

The constraint is the point of `consteval`, but it makes the function unusable from generic runtime code. Detection is the compile error.

## The fix (`good.cpp`)

Pass a constant (`constexpr int n = 5;`), or declare the function `constexpr` if run-time calls must be allowed. The fixed program prints `25`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

