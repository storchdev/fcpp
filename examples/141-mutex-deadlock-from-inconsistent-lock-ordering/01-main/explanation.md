# 141 — Mutex deadlock from inconsistent lock ordering

## Why the bad code is wrong (`bad.cpp`)

One path locks `a` then `b`, the other `b` then `a`. If the two paths run concurrently, each thread can hold one mutex and wait for the other forever; whether that happens depends on timing, so the program may run correctly for a long time. The demo runs the two threads one after the other so it terminates and prints `finished (run sequentially here, but concurrent runs can deadlock)`, but the order inversion is still recorded.

ThreadSanitizer reports `lock-order-inversion (potential deadlock)` at `-O0`, `-O1` and `-O2` with both compilers, even though the run did not deadlock. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Acquire multiple mutexes together with `std::scoped_lock lk(a, b)` (or `std::lock`), which uses a deadlock-avoidance algorithm so the order of arguments in different threads does not matter; or impose one global lock order. The fixed program runs both threads concurrently with opposite argument orders, prints `finished`, and TSan has nothing to report.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

