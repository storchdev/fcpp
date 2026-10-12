# 139 — Condition-variable spurious wakeups

## Why the bad code is wrong (`bad.cpp`)

`condition_variable::wait(lock)` without a predicate returns whenever the thread is woken: by a matching `notify`, by a notification meant for another condition, or spuriously (the standard permits `wait` to unblock without a notification). A wakeup is therefore not evidence that the state the waiter cares about has changed. The program stands in for a stray wakeup by calling `notify_one()` without setting `ready`; the waiter returned and printed `woke up, ready = 0` with both compilers at `-O0` and `-O2`. I did not observe a truly spurious wakeup, so the notify without a state change is the demonstration, not proof of one.

The code is well-defined; the bug is acting on a condition that does not hold. Neither compiler warns under `-Wall -Wextra`, and no tool I ran flags a predicate-less `wait`.

## The fix (`good.cpp`)

Always wait with a predicate: `cv.wait(lk, [] { return ready; })` is defined as a loop `while (!pred()) wait(lk);`, so a stray wakeup sends the thread back to sleep. The fixed program takes the same stray notify, ignores it, and prints `woke up, ready = 1`; the state is changed under the mutex before the real notification.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

