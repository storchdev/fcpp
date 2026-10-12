# 055.01 — Over-aligned allocation and packed structures: `malloc` for an over-aligned type

## Why the bad code is wrong (`bad.cpp`)

`std::malloc` returns memory aligned for any fundamental type (`alignof(std::max_align_t)`), which is not enough for `alignas(64) Block`. Constructing a `Block` at a pointer that is not a multiple of 64 violates the type's alignment requirement: undefined behavior. A second small allocation (`first`) is made before the `Block` memory so that the allocator state makes the failure visible; the actual address depends on the allocator.

With `-fsanitize=undefined` (`-std=c++17 -O1`) both compilers report it: g++ 16.2.1 `runtime error: store to misaligned address 0x… for type 'struct Block', which requires 64 byte alignment`; clang++ 23.1.1 `runtime error: constructor call on misaligned address 0x… for type 'Block', which requires 64 byte alignment`. If the address happens to be a multiple of 64 the program runs without a report, so a clean run proves nothing. No `-Wall -Wextra` warning; none of the clang-tidy checks I ran flagged it.

## The fix (`good.cpp`)

In C++17, `new Block` and `std::make_unique<Block>()` call the aligned form of `operator new` for over-aligned types, so the allocation is correctly aligned. For C-style allocation use `std::aligned_alloc(alignof(Block), sizeof(Block))` (size a multiple of the alignment) and release it with `std::free`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
