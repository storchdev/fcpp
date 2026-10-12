# 143.02 — `std::async` execution policy surprises: deferred never ready

## Why the bad code is wrong (`bad.cpp`)

With `std::launch::deferred`, the callable runs lazily on the thread that calls `get()` or `wait()`; no thread is created. `wait_for` and `wait_until` return `std::future_status::deferred` immediately and the task never becomes ready by polling, so a loop `while (f.wait_for(...) != ready)` would spin forever. The program caps the loop at 5 polls, and printed `polls = 5, status is deferred: 1` with both compilers at `-O0` and `-O2`. (With the default policy, `launch::async | launch::deferred`, the implementation chooses; I did not test which one libstdc++ picks here.)

Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Request a thread explicitly with `std::launch::async` when the work must run concurrently, or call `get()` / `wait()` on a deferred task. The fixed program prints `result = 7`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

