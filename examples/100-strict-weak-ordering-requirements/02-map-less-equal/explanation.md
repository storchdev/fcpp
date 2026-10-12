# 100.02 — Strict weak ordering requirements: `map` with `less_equal`

## Why the bad code is wrong (`bad.cpp`)

`std::map` considers two keys equivalent when neither is less than the other: `!comp(a, b) && !comp(b, a)`. With `std::less_equal`, `comp(1, 1)` is true, so key 1 is never equivalent to itself: the second `insert` finds no equivalent key and adds a duplicate, and `find(1)` and `count(1)` cannot find either entry. The program printed `size = 2, count(1) = 0, find(1) fails` with both compilers at `-O0` and `-O2`.

The comparator is not a strict weak ordering, so the container's requirements are violated (undefined behavior). The observed result is a corrupt container rather than a crash, and it makes `map` look broken. Neither compiler warns under `-Wall -Wextra`, and no sanitizer reports it.

## The fix (`good.cpp`)

Use `std::less` (the default). For `multimap`/`multiset` duplicates are allowed already, with `<`. The fixed program prints `size = 1, count(1) = 1, find(1) succeeds`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
