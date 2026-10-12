# 140 — Lost wakeups and predicate synchronization

## Why the bad code is wrong (`bad.cpp`)

A condition variable has no memory: `notify_one()` only wakes a thread that is already blocked in a wait. Here the notifier runs to completion before the main thread waits, so the notification is lost and nothing remains to indicate that it happened. A plain `wait()` would then block forever (I did not run that variant, because it hangs). The program uses `wait_for` with 200 ms so that it terminates, and it timed out: `woken = 0` with both compilers at `-O0` and `-O2`.

The code is well-defined; the failure is a hang (or timeout). Neither compiler warns under `-Wall -Wextra` and no tool I ran flags it. TSan was not run on it.

## The fix (`good.cpp`)

Put the fact in shared state protected by the same mutex the waiter uses, change it before notifying, and wait with a predicate. The predicate is checked before blocking, so it returns at once if the notification already happened. The fixed program prints `woken = 1` with both compilers.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

