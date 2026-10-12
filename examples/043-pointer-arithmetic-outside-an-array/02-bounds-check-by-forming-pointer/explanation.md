# 043.02 — Pointer arithmetic outside an array: checking a bound by forming the pointer

## Why the bad code is wrong (`bad.cpp`)

`buf + n <= end` tries to test "does `n` more bytes fit" by computing the pointer first. But `buf + n` is itself undefined unless the result lies within the array or one past its end, so the check can only be trusted for inputs that are already valid. With `n = SIZE_MAX` the addition also wraps. Both g++ 16.2.1 and clang++ 23.1.1 print `fits(SIZE_MAX) = 1`: the check accepted an impossible length. Because the arithmetic is undefined, an optimizer may also assume `buf + n >= buf` and delete such checks entirely; I did not observe that here.

Sanitizer support differs between the compilers (`-std=c++17 -O1 -fsanitize=undefined`): clang++ reports `runtime error: addition of unsigned offset to 0x… overflowed to 0x…`; g++ printed no report for the same program, with either `-fsanitize=undefined` or `-fsanitize=pointer-overflow`. For that reason `bad.cpp` has no sanitizer header and `detection` is `none`: the checker only verifies g++.

## The fix (`good.cpp`)

Compare sizes: `n <= static_cast<std::size_t>(end - buf)`. The subtraction is between two pointers into the same array, which is defined, and no out-of-range pointer is ever formed.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
