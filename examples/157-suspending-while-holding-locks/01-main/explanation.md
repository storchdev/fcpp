# 157 — Suspending while holding locks

## Why the bad code is wrong (`bad.cpp`)

A `std::lock_guard` that is a local of a coroutine lives in the coroutine frame, so it remains locked across `co_await`. While the coroutine is suspended, every other thread that needs the mutex is blocked or fails to get it: the program shows this with `try_lock` from another thread and printed `other thread acquired the mutex while the coroutine was suspended: 0` with both compilers at `-O0` and `-O2`. Also, `std::mutex::unlock` requires that the mutex is owned by the calling thread (cppreference: otherwise the behavior is undefined), so if the coroutine resumes on a different thread (as with a thread-pool executor) the guard's destructor unlocks a mutex it does not own. I did not run that variant.

Neither compiler warns under `-Wall -Wextra`, and no tool I ran flags it.

## The fix (`good.cpp`)

End the critical section before the suspension point (scope the guard, as in `good.cpp`), and re-acquire the lock after resuming if needed. The fixed program prints `other thread acquired the mutex while the coroutine was suspended: 1`.

## Rust (no `good.rs`)

In Rust a `MutexGuard` is not `Send`, so holding one across an `.await` in a future that must be `Send` is rejected by the compiler (not verified here). No Rust equivalent is provided for this case.

