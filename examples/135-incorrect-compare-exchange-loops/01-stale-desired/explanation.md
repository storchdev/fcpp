# 135.01 — Incorrect compare-exchange loops: stale desired value

## Why the bad code is wrong (`bad.cpp`)

On failure `compare_exchange_weak` writes the current value into `expected`, so the retry compares against the fresh value, but `desired` was computed once before the loop from the old one. A retry therefore stores `old + 1` over a newer value, discarding other threads' updates. The program printed `counter = 111671`, `102019` (g++ `-O0`, `-O2`) and `100344`, `111089` (clang++ `-O0`, `-O2`) instead of 200000; the numbers vary per run.

There is no data race, TSan has nothing to report, and neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Recompute the desired value from `expected` on every attempt, as in `good.cpp`: `compare_exchange_weak(expected, expected + 1)` inside the loop. The fixed program prints `counter = 200000 (expected 200000)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

