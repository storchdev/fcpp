# 058 — Signed/unsigned comparisons

## Why the bad code is wrong (`bad.cpp`)

When the operands of a relational operator have different signedness, the usual arithmetic conversions bring them to a common type; for `int` against `unsigned int` (or `std::size_t`) that type is the unsigned one, so the signed operand is converted to it. Converting a negative value to an unsigned type is defined (modulo 2^N), so `-1` becomes `UINT_MAX` and `-1 < 1u` is `false`. Nothing is undefined; the program simply compares different numbers than the ones written.

The second comparison is the common real-world form: `idx < v.size()` with `int idx = -1`. `idx` becomes `std::size_t` 18446744073709551615, the test is false, and the demo prints "out of range", which is the right answer for the wrong reason.

Both compilers warn with `-Wsign-compare` under `-Wall -Wextra` (see `compilers.md` for the texts). Reviewers miss it because the warning is routinely silenced with a cast, and a cast on the wrong operand hides the bug instead of fixing it.

## The fix (`good.cpp`)

C++20 adds `std::cmp_less` and the other `std::cmp_*` functions in `<utility>`, which compare the mathematical values. Without C++20, check the sign first (`idx >= 0 && static_cast<std::size_t>(idx) < v.size()`), or keep indices in one type. Casting `v.size()` to `int` trades this bug for a truncation bug on large containers.

## Rust (`good.rs`)

Rust has no implicit integer conversions, so `a < b` with `a: i32` and `b: u32` is a type error (`E0308`). You widen both sides to a common type (`i64::from`) or convert with `usize::try_from(idx)`, which returns `Err` for negative values.
