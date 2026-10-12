# 092.02 — `std::vector` reallocation invalidation: insert shifts elements

## Why the bad code is wrong (`bad.cpp`)

`insert` invalidates every iterator at or after the insertion point even when no reallocation happens, because the elements are moved. If the capacity was exceeded, all iterators are invalidated. Here `reserve(100)` rules reallocation out, `it` points at the slot that held `3`, and after `v.insert(v.begin(), 0)` that slot holds `2`, so `*it` prints `2` instead of `3` with both compilers at `-O0` and `-O2`. The iterator is invalid, so using it is undefined behavior; the compilers just happen to read the shifted element.

This is the harder variant to spot because the program does not crash and no memory error occurs: there is simply a different element behind the iterator. Neither compiler warns under `-Wall -Wextra`, and no sanitizer reports it (the access stays inside the allocation).

## The fix (`good.cpp`)

Do the `find` after the modification, or use the iterator that `insert` returns. The fixed program prints `*it = 3`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
