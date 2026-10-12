# 057 — Unsigned arithmetic wraparound

## Why the bad code is wrong (`bad.cpp`)

Unsigned integer arithmetic is defined to wrap modulo 2^N (N is the width of the type), so nothing here is undefined behavior. The bugs come from writing code as if the values were mathematical integers. `v.size()` has type `std::size_t`; for an empty vector `v.size() - 1` is `SIZE_MAX` (18446744073709551615 on this platform), not `-1`. Any later `i <= last` or `v[last]` is then wrong, and the code that computed it looks perfectly reasonable.

The second bug is the countdown loop. `i >= 0` is true for every `unsigned` value, so the loop never terminates by its condition: after `i = 0` the decrement produces `UINT_MAX`. In the demo a counter breaks out after six iterations, and the output goes `3, 2, 1, 0, 4294967295, 4294967294`. In real code this is a hang or an out-of-bounds index, often discovered only on the input that reaches zero (the empty container, the first element).

It survives review because the same expression is correct when the operand is signed, and because `size()` returns an unsigned type only by convention. Detection: g++ warns about the loop with `-Wtype-limits` under `-Wall -Wextra`; clang++ does not warn under `-Wall -Wextra` but does with `-Wtautological-unsigned-zero-compare`. Nothing flags `v.size() - 1`: wraparound is defined, so UBSan does not report it. See `compilers.md`.

## The fix (`good.cpp`)

Test before subtracting (`if (v.empty())`), and return something that can express "no last element" (`std::optional`). For the countdown, use the `i-- > 0` idiom: the test happens before the decrement, so the body sees `3, 2, 1, 0` and the loop stops without ever computing `-1`. Another option is to make the index signed, at the cost of signed/unsigned comparisons against `size()` (see entry 058).

## Rust (`good.rs`)

Rust integers wrap only when you ask: `v.len().checked_sub(1)` returns `None` for an empty slice, and `(0..4u32).rev()` has no condition to get wrong. A plain `v.len() - 1` is never UB: it panics in debug builds and wraps in release builds (`rustc -O`).
