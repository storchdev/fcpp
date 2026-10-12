# 059.02 — Integer promotions: `uint16_t * uint16_t`

## Why the bad code is wrong (`bad.cpp`)

The rule from case 01 has a worse consequence for multiplication. Two `std::uint16_t` operands are promoted to `int`, the multiplication is performed as `int * int`, and signed overflow is undefined behavior (see entry 056). `65535 * 65535` is 4294836225, which does not fit in a 32-bit `int`, even though both inputs are unsigned and the destination `std::uint32_t` could hold the value. The widening to `uint32_t` happens only after the multiplication.

The program printed `4294836225` at `-O0` and `-O2` with both compilers, which is the number you would expect, so the bug is invisible in a plain run. `-fsanitize=undefined` reports `runtime error: signed integer overflow: 65535 * 65535 cannot be represented in type 'int'` from both compilers at `-O0`, `-O1` and `-O2`. Neither compiler warned under `-Wall -Wextra`.

It looks like the safe case, "unsigned never overflows", which is why it hides in code that multiplies small unsigned fields.

## The fix (`good.cpp`)

Convert one operand to a type at least as wide as the result *before* multiplying: `std::uint32_t{a} * b`. Now the arithmetic is unsigned 32-bit, and wraparound is defined if the product exceeds it.

## Rust (`good.rs`)

`u16 * u16` is a `u16` multiplication that panics in debug builds and wraps in release builds (never UB). `u32::from(a) * u32::from(b)` widens first, and `a.checked_mul(b)` reports `None`.
