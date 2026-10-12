# 119.02 — `constexpr`, `consteval`, and `constinit`: constexpr is not a guarantee

## Why the bad code is wrong (`bad.cpp`)

`constexpr` permits evaluation at compile time but a call is only evaluated at compile time when it appears where a constant expression is required (such as the initializer of a `constexpr` variable). `int a = where();` is an ordinary initialization, and `std::is_constant_evaluated()` returned false there: the program printed `a = 0 (1 means compile time), b = 1` with both compilers at `-O0` and `-O2`.

The result is well-defined, but code that relies on `constexpr` for a compile-time cost, or for a side-effect-free guarantee, gets run-time behavior. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `consteval` when every call must be compile-time, or force it with `constexpr int a = ...`. The fixed program prints `a = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

