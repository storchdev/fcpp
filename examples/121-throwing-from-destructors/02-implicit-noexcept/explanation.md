# 121.02 — Throwing from destructors: implicit noexcept

## Why the bad code is wrong (`bad.cpp`)

Since C++11 a user-declared destructor without an exception specification is implicitly `noexcept(true)` (unless a base or member destructor is `noexcept(false)`). An exception leaving it therefore calls `std::terminate`, even with no exception in flight, so the `catch` is skipped. The output was `terminate called after throwing an instance of 'std::runtime_error'` with `what(): close failed` and a core dump on both compilers at `-O0` and `-O2`.

Both compilers warn without extra flags: g++ "‘throw’ will always call ‘terminate’ [-Wterminate]" and clang++ "'~File' has a non-throwing exception specification but can still throw [-Wexceptions]". `clang-tidy -checks=bugprone-exception-escape` also reports it ("an exception may be thrown in function '~File' which should not throw exceptions").

## The fix (`good.cpp`)

Never throw out of a destructor: provide an explicit `close()` that can fail and report an error, and keep the destructor non-throwing. The fixed program prints `close failed, handled by the caller`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

