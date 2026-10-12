# 094.01 — `std::deque` invalidation rules: reference across a middle insert

## Why the bad code is wrong (`bad.cpp`)

For `std::deque`, an insertion in the middle invalidates all iterators and all references to elements, which is stricter than the rule for `push_back`/`push_front` (case 02). After `d.insert(d.begin() + 1, 99)`, `second` is therefore an invalid reference and reading it is undefined behavior. The program printed `second = 99 (expected 2)` with both compilers at `-O0` and `-O2`: the slot `second` refers to now holds the inserted value (an implementation detail, not something to rely on).

Because deque storage is segmented, there is no reallocation to crash on, and the access stays in valid memory, so sanitizers have nothing to report. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Take the reference after the insert (or hold an index). The fixed program prints `second = 2`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
