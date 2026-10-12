# 179 — Compile-time vs. runtime computation

## Why the bad code is wrong (`bad.cpp`)

`constexpr` allows evaluation at compile time but does not require it: `square(n)` with a run-time `n` runs at run time, and `square(5)` initializing an ordinary `int` is not a constant-evaluated context either, so `std::is_constant_evaluated()` is false there. The sign shows it: both calls printed positive 25 (`square(n) = 25, square(5) = 25`) with both compilers at `-O0` and `-O2`. The optimizer may still fold the call; the language does not promise it.

A `consteval` function must be called in a constant expression: calling `sq(n)` with a run-time `n` is an error, g++ `error: call to consteval function ‘sq(n)’ is not a constant expression` and clang++ `error: call to consteval function 'sq' is not a constant expression` (checked with a scratch program). Neither compiler warns about `bad.cpp` under `-Wall -Wextra`.

## The fix (`good.cpp`)

Force compile-time evaluation where you need it: initialize a `constexpr` variable (as in `good.cpp`, which prints `square(5) = -25 (negative means compile time)`), or make the function `consteval`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

