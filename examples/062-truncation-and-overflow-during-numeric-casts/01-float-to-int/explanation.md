# 062.01 — Truncation and overflow during numeric casts: floating point to integer

## Why the bad code is wrong (`bad.cpp`)

A floating-to-integer conversion truncates toward zero. If the truncated value cannot be represented in the destination type, the behavior is undefined (a NaN is also reported by the sanitizer as outside the range of `int`). `1e10` is far outside `int`, so `static_cast<int>(1e10)` is UB; it is not saturation and not wraparound.

On this machine both compilers printed `-2147483648` at `-O0` and `-O2`, so the program appears to "work" with a plausible-looking wrong number. The standard permits any result.

`-fsanitize=undefined` does not include this check on either compiler; it is the separate `-fsanitize=float-cast-overflow`, which both compilers accept and which reports `1e+10 is outside the range of representable values of type 'int'` at `-O0`, `-O1` and `-O2`. `-Wconversion` stays silent here because the cast is explicit.

## The fix (`good.cpp`)

Range-check before converting, writing the test so that NaN fails it (`!(d > lo && d < hi)`), and return a value that can say "out of range".

## Rust (`good.rs`)

`as` from float to integer is defined to saturate: `1e10 as i32` is `2147483647` and `NaN as i32` is `0`. `i32::try_from` is the explicit checked route (it does not accept floats, so the demo goes through `i64`).
