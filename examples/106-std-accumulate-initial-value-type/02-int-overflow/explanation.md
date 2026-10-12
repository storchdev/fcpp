# 106.02 — `std::accumulate` initial-value type: overflow

## Why the bad code is wrong (`bad.cpp`)

The accumulator is an `int`, so `INT_MAX + 1` is signed overflow, which is undefined behavior, in the library's `acc = acc + *first` (reported at `stl_numeric.h:140`). The elements are `int` too, so the width of `0` is the only thing that could have saved it. A plain run printed `sum = -2147483648` with both compilers at `-O0` and `-O2` (the wrapped value on this hardware; the standard does not say so).

UndefinedBehaviorSanitizer reports `signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'` at `-O0`, `-O1` and `-O2` with both compilers. The warning machinery cannot see inside the library call, so neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use a wider initial value (`0LL`), so the sum is computed in `long long`. The fixed program prints `sum = 2147483648`.

## Rust (`good.rs`)

Integer overflow is never silently undefined: it panics in debug builds and wraps in release builds, and the explicit APIs make the choice visible (`checked_add`, widening with `i64::from`). The demo prints `checked i32 sum = None, i64 sum = 2147483648`.
