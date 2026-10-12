# 143.01 — `std::async` execution policy surprises: discarded future

## Why the bad code is wrong (`bad.cpp`)

The future returned by `std::async(std::launch::async, ...)` is special: its destructor blocks until the task finishes. Discarding the return value destroys that future at the end of the statement, so the "asynchronous" call completes before the next line. The program printed `task finished` and then `launched` with both compilers at `-O0` and `-O2`, i.e. the call was effectively synchronous.

The code is well-defined. Both compilers warn because `std::async` is `[[nodiscard]]`: g++ `[-Wunused-result]` ("ignoring return value of ‘std::future<...> std::async(...)’") and clang++ `[-Wunused-result]` ("ignoring return value of function declared with 'nodiscard' attribute") under `-Wall -Wextra`.

## The fix (`good.cpp`)

Keep the future in a variable for as long as the task should run in the background and call `get()` or `wait()` when the result is needed. The fixed program prints `launched` first and then `task finished`, with both compilers.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

