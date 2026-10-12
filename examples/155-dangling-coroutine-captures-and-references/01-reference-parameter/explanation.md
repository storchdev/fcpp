# 155.01 — Dangling coroutine captures and references: reference parameter

## Why the bad code is wrong (`bad.cpp`)

A coroutine copies its parameters into the frame, but a reference parameter is copied as a reference, not as the object it refers to. With `initial_suspend` returning `suspend_always`, the body does not run during the call: the temporary `std::string` argument is destroyed at the end of the full-expression, and `resume()` later reads a dead string through the reference, which is undefined behavior. Plain runs printed garbage after `hello ` with both compilers at `-O0` and `-O2` (the exact bytes vary).

AddressSanitizer reports `stack-use-after-scope` for g++ at `-O0`, `-O1` and `-O2` and for clang++ at `-O0` and `-O1`; clang++ at `-O2` reports `heap-use-after-free`. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Take the parameter by value: it is copied (or moved) into the coroutine frame and lives as long as the frame. The fixed program prints `hello a name long enough to live on the heap, not in SSO`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

