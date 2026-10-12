# 051 — Struct padding and object representations

## Why the bad code is wrong (`bad.cpp`)

`Key` is `char` + `int`: on this ABI `sizeof(Key)` is 8, with three padding bytes after `tag` (checked with `static_assert(sizeof(Key) == 8)`). Padding bytes are part of the object representation but not of its value, and their contents are unspecified; the compiler is free to leave, copy or overwrite them. `std::has_unique_object_representations_v<Key>` is false (asserted), which is the trait that says whether two equal values must have equal bytes.

`bad.cpp` simulates stale memory by filling one object with `0x00` and another with `0xFF` before assigning the same field values. The program prints `fields equal: 1, memcmp equal: 0` on both g++ 16.2.1 and clang++ 23.1.1: the same value, different bytes. The same hazard applies to hashing the bytes of a struct, serializing it with `fwrite`/`send` (the padding can leak stale data), and using it as a key in a byte-wise container. Reviews miss it because values assigned field-by-field usually look identical in tests: here the fill is explicit, and `fill` is `noinline` so the compiler cannot merge the stores.

Detection: clang-tidy `bugprone-suspicious-memory-comparison` reports `comparing object representation of type 'Key' which does not have a unique object representation; consider comparing the members of the object manually`. MemorySanitizer did not report anything on this program (all bytes were initialized by the `memset`), and neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Compare members; a defaulted `operator==` (C++20) does that. For hashing and serialization, process each member (or pack explicitly into a byte buffer of defined layout).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
