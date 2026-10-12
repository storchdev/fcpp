# 133.02 — Sequential consistency misconceptions: plain data

## Why the bad code is wrong (`bad.cpp`)

`seq_cst` is a property of the atomic operations that use it: it gives them a single total order and makes them synchronize with each other. `shared_total` is a plain `int`, and `turn.fetch_add(1)` does not protect it: two threads incrementing it unsynchronized is a data race and undefined behavior. A plain run printed `turn = 2, shared_total = 2` with both compilers, which hides the problem.

ThreadSanitizer reports `data race` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Make the shared data atomic (as in `good.cpp`) or protect it with a mutex that every access takes. The fixed program prints `turn = 2, shared_total = 2` and TSan has nothing to report.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

