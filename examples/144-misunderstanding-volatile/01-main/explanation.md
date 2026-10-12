# 144 — Misunderstanding `volatile`

## Why the bad code is wrong (`bad.cpp`)

`volatile` makes each access an observable side effect that the compiler must perform, but it does not make `counter = counter + 1` atomic, does not create happens-before edges, and does not exempt the object from data-race rules. Two threads doing that on a `volatile int` is a data race, which is undefined behavior, and increments are lost. The program printed `counter = 115337` and `118508` (g++ `-O0`, `-O2`) and `108212`, `145373` (clang++ `-O0`, `-O2`) instead of 200000; the numbers vary per run.

ThreadSanitizer reports `data race` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `std::atomic<int>` with `fetch_add` (or a mutex). `volatile` is for memory-mapped I/O and similar, where each access must really happen. The fixed program prints `counter = 200000 (expected 200000)` with both compilers.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

