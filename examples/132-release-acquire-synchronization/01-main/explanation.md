# 132 — Release/acquire synchronization

## Why the bad code is wrong (`bad.cpp`)

An acquire load synchronizes with a release store only when it reads the value that store wrote, and it orders only the accesses that come after it in the consumer. Here the consumer copies `payload` before the acquire load, so that read has no happens-before relationship with the producer's write: it races with it, which is undefined behavior, even though the same function later spins on an acquire load of the flag.

ThreadSanitizer reports `data race` at `-O0`, `-O1` and `-O2` with both compilers; a plain run printed `payload = 42, copy = 42` on both at `-O0` and `-O2`, which can look correct. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Read the payload only after the acquire load has returned the released value. The fixed program prints `payload = 42, copy = 42`, and TSan has nothing to report.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

