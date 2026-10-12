# 059.01 — Integer promotions: `~` on `uint8_t`

## Why the bad code is wrong (`bad.cpp`)

Before most arithmetic, bitwise and comparison operators are applied, operands of integer types narrower than `int` (`bool`, `char`, `short`, `std::uint8_t`, `std::uint16_t`) are promoted: to `int` if `int` can represent every value of the type, otherwise to `unsigned int`. On this platform `std::uint8_t` and `std::uint16_t` both promote to `int`. The operation is then carried out in `int`, and the result has type `int`.

So `~mask`, with `mask` a `uint8_t` equal to `0x0F`, is `~0x0000000F`: the `int` `0xFFFFFFF0`, which is `-16`. It does not equal `0xF0`, and the comparison `~mask == 0xF0` is always false (the demo prints `~mask is -16, not 0xF0`). The same applies to `a + b` with two `uint8_t` values: the result is `int` 300 (`sizeof` is 4), not a wrapped `uint8_t` 44. Code that expects 8-bit wraparound gets none until the result is stored back into a `uint8_t`.

Reviewers miss it because the source shows only 8-bit types. g++ warns about this particular comparison with `-Wsign-compare` ("comparison of promoted bitwise complement of an unsigned value with constant"); clang++ gives no warning at `-Wall -Wextra` (`compilers.md`). The sum has no warning from either compiler.

## The fix (`good.cpp`)

Narrow the result explicitly with `static_cast<std::uint8_t>(~mask)` before comparing or storing it, so the value you compare is the 8-bit one. If you want the wider result, say so by naming a wider type. Case 02 shows the more dangerous consequence of promotion.

## Rust (`good.rs`)

Rust has no integer promotion: `!mask` on a `u8` is a `u8`, and `a + b` on two `u8` values is a `u8` (panicking on overflow in debug builds, wrapping in release builds). You choose `checked_add`, `wrapping_add`, or widen with `u16::from`.
