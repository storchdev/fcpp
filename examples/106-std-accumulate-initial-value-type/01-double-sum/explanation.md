# 106.01 — `std::accumulate` initial-value type: truncation

## Why the bad code is wrong (`bad.cpp`)

`std::accumulate(first, last, init)` computes in the type of `init`: `T acc = init; acc = acc + *it` for each element, so with `init == 0` (an `int`) every partial result is converted back to `int`. For `{0.5, 0.5, 0.5, 0.5}` the running value is `int(0 + 0.5) = 0` each step, and the program printed `sum = 0 (expected 2)` with both compilers at `-O0` and `-O2`.

The conversion happens inside the standard library, so the usual conversion warnings do not fire: neither compiler warns under `-Wall -Wextra`. `clang-tidy -checks=bugprone-fold-init-type` reports it: "folding type 'double' into type 'int' might result in loss of precision".

## The fix (`good.cpp`)

Pass an initial value of the intended type (`0.0`, `0LL`, `std::string{}`), or in C++17 consider `std::reduce` (which also requires an associative operation, see entry 107). The fixed program prints `sum = 2`.

## Rust (`good.rs`)

Folding `f64` elements into an integer `0` is rejected (`E0277`: cannot add `&f64` to `{integer}`); `iter().sum::<f64>()` states the type. The demo prints `sum = 2`.
