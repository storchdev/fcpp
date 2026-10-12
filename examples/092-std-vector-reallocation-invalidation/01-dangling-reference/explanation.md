# 092.01 — `std::vector` reallocation invalidation: dangling reference

## Why the bad code is wrong (`bad.cpp`)

When `push_back` needs more room than `capacity()`, `std::vector` allocates a new block, moves or copies the elements, and frees the old block. All iterators, pointers and references into the vector are then invalid, and using them is undefined behavior. In `bad.cpp` the loop leaves `size() == capacity() == 4` (printed capacity 4 in a scratch run with both compilers), so the fifth element forces reallocation and `first` points into freed memory.

A plain run printed a garbage value (different on every run) with both compilers at `-O0` and `-O2`; nothing crashes, which is why this is found late. It is easy to write when the reference is taken in one function and the vector is grown in another, and the capacity makes it data-dependent: with spare capacity the same code appears to work.

AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Take references, pointers and iterators after the last operation that can grow the vector, or hold an index (`v[0]`) instead of a reference, or `reserve` enough capacity up front and rely on the documented guarantee that no reallocation occurs while `size() <= capacity()`. The fixed program prints `first = 0` and `v[0] = 0`.

## Rust (`good.rs`)

The borrow checker rejects the bad shape: with `let first = &v[0]; v.push(4); use first`, rustc reports `E0502` ("cannot borrow `v` as mutable because it is also borrowed as immutable"). The demo borrows after the `push` and prints `first = 0`.
