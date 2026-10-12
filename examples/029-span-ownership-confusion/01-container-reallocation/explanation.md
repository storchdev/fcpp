# 029.01 — `std::span` ownership confusion: container reallocation

## Why the bad code is wrong (`bad.cpp`)

`std::span<int> view(v)` stores the address of `v`'s current buffer and its size. It does not register with the vector. `v.resize(1000)` exceeds the capacity (4), so the vector allocates a new buffer, moves the elements, and frees the old one; any pointer, reference, iterator **or span** into it is invalidated. `view[0]` reads the freed buffer: undefined behavior, reported as `heap-use-after-free` by AddressSanitizer on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++20 -O1`).

A span kept in a variable or member across statements that mutate the owner follows the same invalidation rules as iterators and references. Neither compiler warns under `-Wall -Wextra` and none of the clang-tidy checks I ran flagged it; the sanitizer is the detector.

## The fix (`good.cpp`)

Create the span after the last operation that can reallocate (`resize`, `push_back`, `insert`, …), or re-create it after each mutation. Prefer to pass `std::span` into functions rather than to keep one.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
