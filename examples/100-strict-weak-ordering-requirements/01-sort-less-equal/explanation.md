# 100.01 — Strict weak ordering requirements: `sort` with `<=`

## Why the bad code is wrong (`bad.cpp`)

`std::sort` requires `comp` to be a strict weak ordering; in particular `comp(x, x)` must be false. `a <= b` returns true for equal elements, which violates this, and the behavior of the algorithm is undefined. Library sorts rely on the ordering to stop their inner loops: with 100 equal elements the partition and insertion loops never see a "not less" answer and walk past the ends of the range.

AddressSanitizer reports `heap-buffer-overflow` at `-O0`, `-O1` and `-O2` with both compilers, while a plain run printed `sorted 100 elements` and exited normally. The failure depends on the data: a vector with distinct elements would sort correctly, which is why `<=` survives testing. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `<` (or `std::less`), which is irreflexive; for multi-key comparisons compare with `<` on each key and fall through only when neither is less (`std::tie` does this). The fixed program prints `sorted 100 elements`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
