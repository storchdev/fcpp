# 130 — Atomicity vs. visibility vs. ordering

## Why the bad code is wrong (`bad.cpp`)

`counter.store(counter.load() + 1)` is two atomic operations, not one: both threads can load the same value and both store the same result, so increments are lost. Every access is atomic and there is no data race (so no data-race undefined behavior), but the result is wrong. The program printed values near half of the expected total in each plain run: `counter = 106466`, `116077` (g++ `-O0`, `-O2`) and `110095`, `112079` (clang++ `-O0`, `-O2`) instead of 200000. The exact numbers vary from run to run.

The bug is easy to write because each call looks atomic. ThreadSanitizer has nothing to report (atomics are not races), neither compiler warns under `-Wall -Wextra`, and no tool I ran detects it. Atomicity (one indivisible operation), visibility (when a write can be seen) and ordering (relative to other accesses) are separate properties; the memory orders only change the latter two.

## The fix (`good.cpp`)

Use a single read-modify-write: `fetch_add(1)` (or a compare-exchange loop for more complex updates). The fixed program prints `counter = 200000 (expected 200000)`; it is correct under any interleaving.

## Rust (no `good.rs`)

Rust has the same trap: `AtomicI32::load` followed by `store` is also two operations. No Rust equivalent is provided for this case.

