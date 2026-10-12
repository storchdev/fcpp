# 104.02 — Algorithms with invalid ranges or iterators: mismatched containers

## Why the bad code is wrong (`bad.cpp`)

`[first, last)` must denote a range inside one container, reachable from `first` by incrementing. `a.begin()` and `b.end()` belong to different allocations, so the pair is not a range, and `std::sort` is undefined: it sorts however many elements lie between two unrelated addresses (here far beyond the three elements of `a`). Both compilers' plain runs aborted with `munmap_chunk(): invalid pointer` (core dumped) at `-O0` and `-O2`, so the heap was corrupted.

AddressSanitizer stops with `SEGV on unknown address` at `-O0`, `-O1` and `-O2` with both compilers (it is reported as a sanitizer error, not as an overflow). The typo is easy to make when two similar containers are in scope and the compiler cannot tell: both iterators have the same type. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use both iterators from the same container, or avoid the pair altogether with C++20 ranges (`std::ranges::sort(a)`). The fixed program prints `done`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
