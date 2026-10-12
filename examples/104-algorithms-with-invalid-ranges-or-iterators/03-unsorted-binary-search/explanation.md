# 104.03 — Algorithms with invalid ranges or iterators: `binary_search` on unsorted data

## Why the bad code is wrong (`bad.cpp`)

`std::binary_search` requires the range to be partitioned with respect to the searched value (in practice, sorted); otherwise the result is not defined by the standard. The program searched `{5, 1, 4, 2, 3}` and printed `binary_search(4) = 1` but `binary_search(1) = 0` although `1` is present, with both compilers at `-O0` and `-O2`. The first answer is correct by luck.

Nothing crashes and nothing tells you: the failure is a wrong answer that depends on the data. Neither compiler warns under `-Wall -Wextra`, and no sanitizer applies.

## The fix (`good.cpp`)

Sort the range first (or keep it in a `std::set`/sorted container), and keep the comparator used for sorting the same as for searching. The fixed program prints `binary_search(4) = 1` and `binary_search(1) = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
