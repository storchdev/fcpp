# 097.02 — Erasing while iterating: `vector`

## Why the bad code is wrong (`bad.cpp`)

`v.erase(it)` shifts the following elements down and invalidates `it` and everything after it. The loop then does `++it`, which is undefined behavior on an invalid iterator; in practice the iterator moves one slot further and skips the element that was shifted into position `it`. For `{2, 4, 6, 1}` the program printed `size = 2: 4 1` with both compilers at `-O0` and `-O2`: `2` and `6` were removed but `4`, which is even, stayed.

Here nothing crashes and no sanitizer fires (the accesses stay inside the vector's allocation), so only the output reveals it. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use the erase-remove idiom (`v.erase(std::remove_if(...), v.end())`), `std::erase_if(v, pred)` in C++20, or write the loop with `it = v.erase(it)` and `++it` only when nothing was erased. The fixed program prints `size = 1: 1`.

## Rust (`good.rs`)

Erasing inside a `for` loop over the same `Vec` is rejected by the borrow checker (`E0502`: cannot borrow `v` as mutable because it is also borrowed as immutable). `Vec::retain` does the filtering and the demo prints `size = 1: [1]`.
