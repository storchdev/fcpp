# 053.02 — Mismatched allocation and deallocation: `malloc` with `delete`

## Why the bad code is wrong (`bad.cpp`)

`malloc`/`free`, `new`/`delete` and `new[]`/`delete[]` are separate pairs; they may use different allocators or bookkeeping, and mixing them is undefined behavior. Here `delete p` is applied to memory from `std::malloc`. (The reverse, `free` on `new`ed memory, is equally undefined.) A `delete` of a pointer to a class type would also run a destructor on an object that `malloc` never constructed.

AddressSanitizer reports `alloc-dealloc-mismatch (malloc vs operator delete)` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`). g++ also warns under `-Wall -Wextra` with the same `-Wmismatched-new-delete` message as case 01; clang++ 23.1.1 emitted no warning for this one. clang-tidy `clang-analyzer-unix.MismatchedDeallocator` reports `Memory allocated by 'malloc()' should be deallocated by 'free()', not 'delete'`.

## The fix (`good.cpp`)

Use one family per allocation. Here the object is created with `std::make_unique` and the unique pointer's deleter matches. If C allocation is required (a C API hands you the buffer), pair `malloc` with `free` and wrap it in a smart pointer with a custom deleter.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
