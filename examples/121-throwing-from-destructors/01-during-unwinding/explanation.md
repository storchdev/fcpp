# 121.01 — Throwing from destructors: during unwinding

## Why the bad code is wrong (`bad.cpp`)

While `std::logic_error` propagates, stack unwinding destroys `g`, whose `noexcept(false)` destructor throws a second exception. A destructor exit by exception during unwinding calls `std::terminate`, so the `catch` is never reached. It is defined behavior, not UB: the program aborts. The output was `terminate called after throwing an instance of ...` followed by a core dump on both compilers; see `compilers.md` for which exception type is named.

Only the unwinding case needs the `noexcept(false)` opt-in here; the same cleanup that works in normal flow becomes fatal on the error path, so the bug shows only when something else already failed. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Catch failures inside the destructor (log or swallow them), as in the good code, which prints `cleanup error logged: cleanup failed` and then `caught: original error`. If the failure must be reported, expose an explicit `close()`/`flush()` the caller can use and make the destructor best-effort.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

