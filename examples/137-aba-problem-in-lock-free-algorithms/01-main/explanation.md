# 137 — ABA problem in lock-free algorithms

## Why the bad code is wrong (`bad.cpp`)

The pop reads `head` and its successor, then compares-and-swaps `head` from the old index to the successor. If, in between, other threads pop node 0, pop node 1 and push node 0 back, `head` equals the old value again, so the CAS succeeds, but the successor it installs (node 1) is no longer in the stack. The program replays that interleaving deterministically (the `preempted` hook stands for the other thread running in the gap) and printed `first pop returned node 0; head is now node 1 (node 2 expected)` with both compilers at `-O0` and `-O2`.

It is a logic corruption, not a memory error: no sanitizer reports it and neither compiler warns under `-Wall -Wextra`. In a real program the other thread runs concurrently and the failure is rare and timing-dependent, which is why the gap is simulated here.

## The fix (`good.cpp`)

Make the value change on every update so "unchanged" really means unchanged: pack a version tag with the index (as in `good.cpp`, a 64-bit word with a 32-bit tag), use a double-width CAS, or use a reclamation scheme that stops nodes from being recycled while threads still hold them. The fixed program prints `first pop returned node 0; head is now node 2 (node 2 expected)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

