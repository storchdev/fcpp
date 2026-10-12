# 063.01 — Character signedness: widening and comparison

## Why the bad code is wrong (`bad.cpp`)

`char`, `signed char` and `unsigned char` are three distinct types, and whether plain `char` has a signed or an unsigned representation is implementation-defined. On this x86-64 Linux machine both compilers treat it as signed, so `static_cast<char>(0xE9)` holds the value `-23`. Widening it to `int` (`int widened = c`) gives `-23`, not `233`, and `c == 0xE9` promotes `c` to `int` first and compares `-23` with `233`, which is false. The program printed `widened = -23` and `c != 0xE9` with both compilers at `-O0` and `-O2`.

With `-funsigned-char` the same source printed `widened = 233` and `c == 0xE9` from both compilers (no warnings), so the same code gives two answers depending on a platform or flag choice. Code that treats `char` as "a byte" passes on one target and breaks on another, which is the usual way this shows up: a parser or checksum that is tested on x86 and shipped to a target where plain `char` has the other signedness.

Both compilers warn about the comparison here, with different flags: g++ `-Wtype-limits` ("comparison is always false due to limited range of data type") and clang++ `-Wtautological-constant-out-of-range-compare` ("result of comparison of constant 233 with expression of type 'char' is always false"). Nothing warned about the widening itself.

## The fix (`good.cpp`)

Convert to `unsigned char` (or `std::uint8_t`, or `std::byte`) when the value is a byte, and only then widen or compare. Reserve plain `char` for character data passed to text APIs.

## Rust (`good.rs`)

Rust's `u8` is always unsigned, so `i32::from(0xE9u8)` is `233` on every platform. Rust's `char` is a Unicode scalar value, not a byte: `char::from(b)` turns the byte into `'é'` (U+00E9).
