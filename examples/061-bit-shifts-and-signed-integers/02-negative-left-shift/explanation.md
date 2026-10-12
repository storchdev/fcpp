# 061.02 — Bit shifts and signed integers: left shift of a negative value

## Why the bad code is wrong (`bad.cpp`)

Up to C++17, `E1 << E2` with a signed `E1` is undefined behavior if `E1` is negative (or if the result is not representable). C++20 changed the rule: the result is `E1 * 2^E2` reduced modulo 2^N, so `-1 << 1` is `-2` and no longer undefined. The file is compiled as C++17 to show the old rule.

The demo prints `-2` with both compilers at `-O0` and `-O2`, which is the answer you would expect, so the UB is invisible in a plain run; `-fsanitize=undefined` with `-std=c++17` reports `left shift of negative value -1` from both compilers at `-O0`, `-O1` and `-O2`. Under `-std=c++20` neither compiler's UBSan reported anything for the same source (I ran both). That makes it a footgun for code that must build under several standards, such as a library supporting C++14/17: the code is fine on C++20 and UB elsewhere.

Reviewers miss it because `x << 1` as "multiply by two" is idiomatic, and the negative case seldom reaches tests.

## The fix (`good.cpp`)

Multiply (`x * 2`), which has the same meaning for negative values on all standards (overflow still applies), or shift an unsigned value and convert back when you really want bit manipulation.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
