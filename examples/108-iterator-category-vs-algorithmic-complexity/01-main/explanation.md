# 108 — Iterator category vs. algorithmic complexity

## Why the bad code is wrong (`bad.cpp`)

`std::lower_bound` is written for forward iterators, so it compiles for `std::list`. Its comparison count is logarithmic regardless, but with non-random-access iterators it has to reach the middle element by incrementing: the number of iterator steps is linear in `n`. The program wraps the list iterator in a counting iterator and printed `n = 65536: comparisons = 16, iterator steps = 131066` with both compilers at `-O0` and `-O2`. The complexity the standard states for the comparisons is therefore not the cost you pay on a list.

Nothing is undefined and the answer is correct, so the problem is invisible in tests with small `n`. `std::distance` and `std::advance` have the same cost on bidirectional iterators, which is why generic code that uses them silently becomes O(n) per call. Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it.

## The fix (`good.cpp`)

Use a container whose structure supports the operation: `std::set::lower_bound` (a tree descent) or a sorted `std::vector` with `std::lower_bound` (random access, O(log n) steps). The fixed program finds the element in a `std::set` of the same size and prints `n = 65536: lower_bound = 40000`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
