# 172 — Node-based vs. contiguous containers

## Why the bad code is wrong (`bad.cpp`)

Both loops do the same `O(n)` work, but `std::list` visits nodes scattered over the heap (one dependent pointer load per element, poor cache and prefetch behavior), while `std::vector` reads sequentially. Summing 2000000 shuffled ints 20 times took, over three runs: g++ `-O0` 231–234 ms (list) vs 37 ms (vector), g++ `-O2` 36–37 vs 4, clang++ `-O0` 213–214 vs 70, clang++ `-O2` 35–36 vs 3–4. The list also pays a heap allocation per element when it is built.

The code is well-defined and neither compiler warns under `-Wall -Wextra`. Asymptotic complexity (what a review would check) is identical, which is why this passes review.

## The fix (`good.cpp`)

Prefer `std::vector` (or another contiguous container) for traversal-heavy data; use `std::list` only when its stable iterators and O(1) splice are needed. The fixed program stores the same values in a vector.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

