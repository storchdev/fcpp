# 047.01 — Placement new and object replacement: a misaligned arena

## Why the bad code is wrong (`bad.cpp`)

Placement new constructs an object at the address you give it; the storage must be suitably aligned for the type and large enough. `Arena::allocate(1)` returns `buf + 0` and advances `used` to 1; the next call returns `buf + 1`, an address that is not a multiple of `alignof(double)` (8), and `new (…) double(3.5)` stores into it. The arena's own buffer is correctly `alignas(8)`; the bug is the bump pointer ignoring the alignment of what is placed next.

UndefinedBehaviorSanitizer reports it on both compilers (`-std=c++17 -O1 -fsanitize=undefined`): g++ 16.2.1 `runtime error: store to misaligned address 0x… for type 'double', which requires 8 byte alignment`; clang++ 23.1.1 `runtime error: constructor call on misaligned address 0x… for type 'double', which requires 8 byte alignment`. clang-tidy's analyzer also reports it statically: `clang-analyzer-cplusplus.PlacementNew`: `Storage type is aligned to 1 bytes but allocated type is aligned to 8 bytes`. No `-Wall -Wextra` warning.

## The fix (`good.cpp`)

Round `used` up to the type's alignment before handing out storage: `(used + align - 1) & ~(align - 1)` (valid for power-of-two alignments), and pass `alignof(T)`. Standard facilities (`std::pmr::monotonic_buffer_resource`) do this for you.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
