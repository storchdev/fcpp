# 043.01 — Pointer arithmetic outside an array: indexing past a member array

## Why the bad code is wrong (`bad.cpp`)

`p.hdr[i]` is `*(p.hdr + i)`, and pointer arithmetic is defined only while the result is an element of the array or one past its end. `hdr[4]` would be one past the end, and dereferencing it is not allowed; it does not become "the next member" just because `crc` follows `hdr` in the same struct. The author's intent (`count == 5` covers `hdr` and `crc`) relies on the layout, which the language does not promise (padding, reordering of access-control sections, optimization).

Run with `-fsanitize=undefined` (bounds checking) both compilers report it, but the program continues and prints `110` (1+2+3+4+100): g++ 16.2.1 `runtime error: index 4 out of bounds for type 'int [4]'`; clang++ 23.1.1 `runtime error: index 4 out of bounds for type 'const int[4]'`. AddressSanitizer would not see it (everything stays inside one object), and neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Name the fields you mean: `p.crc` for the checksum and a range-for over `p.hdr`. If a flat sequence is really needed, store a single array.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
