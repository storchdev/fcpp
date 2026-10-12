# 131 — `memory_order_relaxed` misuse

## Why the bad code is wrong (`bad.cpp`)

A relaxed store followed by a relaxed load of the same atomic is atomic, but it creates no happens-before edge. The consumer sees `ready == true`, yet the producer's plain write `payload = 42` is not ordered before the consumer's read, so the two conflicting non-atomic accesses form a data race, which is undefined behavior. A plain run printed `payload = 42` with both compilers at `-O0` and `-O2`; that is what it may look like on any given run, and not evidence of correctness.

ThreadSanitizer reports `data race` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Publish with `store(true, std::memory_order_release)` and consume with `load(std::memory_order_acquire)` (or use the default `seq_cst`). The release store makes all earlier writes visible to a thread whose acquire load reads that value. The fixed program prints `payload = 42` and TSan has nothing to report for it.

## Rust (`good.rs`)

Safe Rust cannot share a plain mutable payload at all: writing a `static mut` is rejected without `unsafe` (`E0133`: use of mutable static is unsafe and requires unsafe function or block), so the payload must be an atomic (as in `good.rs`, where the relaxed payload store is published by the release store) or behind a lock.

