# 063.02 — Character signedness: `char` as an array index

## Why the bad code is wrong (`bad.cpp`)

This is the same implementation-defined signedness as case 01, with a worse consequence. `counts[*p]` indexes a 256-entry table with a plain `char`. For the byte `0xFF` (`'ÿ'` in Latin-1, or the first byte of many UTF-8 sequences, which are `0x80` and above) a signed `char` has the value `-1`, and `counts[-1]` is an out-of-bounds access before the start of the array, which is undefined behavior. With an unsigned `char` the same code is fine, so ASCII-only test data never finds the bug.

The plain run printed `1` with both compilers at `-O0` and `-O2`: the out-of-bounds increment landed on other stack memory and nothing visibly broke. AddressSanitizer reports `stack-buffer-underflow` for the access in g++ at `-O0`, `-O1` and `-O2` and in clang++ at `-O0` and `-O1`; clang++ at `-O2` reported nothing (no `counts` label appears in the `-O2` assembly; I did not investigate further, see `compilers.md`).

Both compilers also warn with `-Wchar-subscripts` under `-Wall -Wextra`, which fires on exactly this "array subscript has type char" pattern.

## The fix (`good.cpp`)

Convert through `unsigned char` before indexing: `counts[static_cast<unsigned char>(*p)]`. The value is then always 0..255, so a 256-entry table is always large enough.

## Rust (`good.rs`)

Indexing needs a `usize`, and a byte is a `u8`, so `counts[usize::from(b)]` is always in range for a 256-entry array; there is no signed byte type that is the default.
