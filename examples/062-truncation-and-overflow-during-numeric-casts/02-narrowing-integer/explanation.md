# 062.02 — Truncation and overflow during numeric casts: integer narrowing and sign changes

## Why the bad code is wrong (`bad.cpp`)

Integer-to-integer conversions never trap. Converting to an unsigned type is defined modulo 2^N: `300` becomes `44` in an `unsigned char` and `-1` becomes `SIZE_MAX` in a `std::size_t`. Converting to a signed type when the value does not fit is implementation-defined before C++20 (C++20 makes it modular). In this program `3000000000LL` stored in an `int` printed `-1294967296` with both compilers at `-O0` and `-O2`. None of this is undefined behavior; the bug is that the value changed silently.

The sign-change line is the dangerous one: a negative `int` stored in a `std::size_t` becomes 18446744073709551615, so `n > v.size()` printed `1`. The same applies to the narrowing of a 64-bit file size or timestamp into an `int`.

Neither compiler warns under `-Wall -Wextra`. With extra flags: g++ has `-Wconversion` (lines 8 and 16) and `-Wsign-conversion` (line 13); clang++ has `-Wshorten-64-to-32` (line 8), `-Wimplicit-int-conversion` (line 16) and `-Wsign-conversion` (line 13). clang++ also has `-fsanitize=implicit-conversion`, which reported all three lines at run time; g++ rejects that option (`unrecognized argument to ‘-fsanitize=’ option`).

## The fix (`good.cpp`)

Range-check before narrowing and reject or clamp; test the sign before converting to an unsigned type. Brace initialization (`int x{big}`) makes narrowing a diagnostic; see entry 004 for how the two compilers differ.

## Rust (`good.rs`)

Rust has no implicit integer conversions. `as` wraps (`3_000_000_000i64 as i32` is `-1294967296`), `i32::try_from` returns `Err` when the value does not fit, and `usize::try_from(-1)` is `Err`.
