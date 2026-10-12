# 061.01 — Bit shifts and signed integers: shift count

## Why the bad code is wrong (`bad.cpp`)

For `<<` and `>>`, if the shift count is negative or is greater than or equal to the width in bits of the promoted left operand, the behavior is undefined. `1u << 32` on a 32-bit `unsigned int` is therefore UB, not `0`. Note that the width that matters is that of the promoted left operand (see entry 059): shifting a `uint8_t` by 9 is fine because it is promoted to `int` (both UBSans stayed silent and the result was 512), but shifting an `int` by 32 is not.

The demo printed `1` for `1u << 32` at `-O0` and `-O2` with both compilers, as if the count had been reduced modulo 32; the standard allows any result. The bug appears when a count is computed (an index into a bitset, `1u << (width - used)`) and an edge case reaches 32.

Detect it with `-fsanitize=undefined`: both compilers report `shift exponent 32 is too large for 32-bit type 'unsigned int'` at `-O0`, `-O1` and `-O2`. Neither warns under `-Wall -Wextra` because the count is not a constant.

## The fix (`good.cpp`)

Check the count against the type's width (`n < 32`) and decide explicitly what an out-of-range count means (0, saturate, or error). Use an unsigned count so a negative one cannot arrive.

## Rust (`good.rs`)

Shifts are checked: `1u32 << 32` panics with "attempt to shift left with overflow" in a debug build and masks the count in a release build (`rustc -O` printed `1`); neither is UB. `checked_shl` returns `None`, and `wrapping_shl` masks the count explicitly.
