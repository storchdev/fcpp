# 174 — Custom allocator and `std::pmr` lifetime errors

## Why the bad code is wrong (`bad.cpp`)

A `std::pmr` container stores a pointer to its `memory_resource` and uses it for every allocation and deallocation; it does not own the resource. `make()` creates a `monotonic_buffer_resource` as a local, builds a vector on it and returns the vector: the move keeps the same allocator, so the returned vector refers to a pool that was destroyed when `make()` returned, and the memory the vector's elements live in was released with it. Reading `v[999]` in `main` is a use after free (undefined behavior). The plain run aborted with a core dump at `-O0` with both compilers and printed `v[999] = 999` at `-O2` with both, which looks fine.

AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Make the resource outlive everything that allocates from it: declare it before the containers (as in `good.cpp`) or in an outer scope, and do not return or store containers beyond the resource's lifetime. The fixed program prints `v[999] = 999` and ASan reports nothing.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

