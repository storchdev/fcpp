# 053.01 — Mismatched allocation and deallocation: `new[]` with `delete`

## Why the bad code is wrong (`bad.cpp`)

An array form `new int[4]` must be released with `delete[]`; `delete values;` applies the scalar form to memory obtained from the array form, which is undefined behavior (for a type with a non-trivial destructor, only the first destructor would run, and the allocator may receive a different pointer or size). For `int` it often appears to work, which is how it persists.

AddressSanitizer reports `alloc-dealloc-mismatch (operator new [] vs operator delete)` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`). Both compilers also warn under `-Wall -Wextra`: g++ `warning: ‘void operator delete(void*, long unsigned int)’ called on pointer returned from a mismatched allocation function [-Wmismatched-new-delete]`; clang++ `warning: 'delete' applied to a pointer that was allocated with 'new[]'; did you mean 'delete[]'? [-Wmismatched-new-delete]`. clang-tidy: `clang-analyzer-unix.MismatchedDeallocator`: `Memory allocated by 'new[]' should be deallocated by 'delete[]', not 'delete'`.

## The fix (`good.cpp`)

Don't pair them by hand: `std::vector<int>` or `std::make_unique<int[]>(4)` (whose deleter is `delete[]`).

## Rust (`good.rs`)

`Box<[T]>`, `Vec<T>` and `Box<T>` each free themselves with the matching allocator call; there is no `delete`/`delete[]` choice.
