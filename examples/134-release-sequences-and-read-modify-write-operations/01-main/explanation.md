# 134 — Release sequences and read-modify-write operations

## Why the bad code is wrong (`bad.cpp`)

A release store heads a release sequence; an acquire load that reads a value written by an element of that sequence synchronizes with the head. In C++20 (and in the C++17 wording for another thread) only read-modify-write operations by other threads continue the sequence: a plain atomic store, even a relaxed one, ends it. The relay thread's `store(2, relaxed)` is not an RMW, so the consumer's acquire load that reads `2` does not synchronize with the producer's release store, and its read of `payload` races with the producer's write: undefined behavior.

ThreadSanitizer did not report it at `-O0`, `-O1` or `-O2` with either compiler in this run, and the plain program printed `payload = 42`. I did not investigate why; the model's rule is what the explanation relies on, not the tool's silence. Neither compiler warns under `-Wall -Wextra`. This is the classic case where a sanitizer is a lower bound: no report here does not mean the code is correct.

## The fix (`good.cpp`)

Make the relay an RMW (`compare_exchange_weak`, `fetch_add`, `exchange`), which continues the release sequence, so the consumer's acquire load still synchronizes with the producer's release store; or have the relay use `release` itself and the consumer synchronize with the relay. The fixed program prints `payload = 42`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

