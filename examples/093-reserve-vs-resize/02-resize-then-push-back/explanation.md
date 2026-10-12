# 093.02 — `reserve()` vs. `resize()`: `push_back` after `resize`

## Why the bad code is wrong (`bad.cpp`)

`resize(3)` value-initializes three elements, so `size()` is 3 right away and every `push_back` appends after them. The program printed `size = 6: 0 0 0 1 2 3` with both compilers at `-O0` and `-O2`. Nothing is undefined: the vector holds what the code asked for, which is not what the author meant ("make room for 3").

The name `resize` reads like "make room", while `reserve` reads like "set aside"; code that mixes the two idioms (`resize` then `push_back`) produces leading zeros that are easy to miss in output and in sums. Neither compiler warns under `-Wall -Wextra`, and no tool reported it.

## The fix (`good.cpp`)

Use `reserve(3)` before the `push_back` loop (capacity only), or `resize(3)` and then assign by index. The fixed program prints `size = 3: 1 2 3`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
