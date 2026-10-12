# 155.02 — Dangling coroutine captures and references: lambda capture

## Why the bad code is wrong (`bad.cpp`)

For a lambda coroutine the captured variables are members of the closure object, and the coroutine frame refers to the closure through `this`; the captures are not copied into the frame. Here the closure is a temporary destroyed at the end of the statement, while the coroutine is resumed afterwards, so the body reads a destroyed `std::string` capture: undefined behavior. The plain runs printed garbage bytes (and no readable text) with both compilers at `-O0` and `-O2`.

AddressSanitizer reports `stack-use-after-scope` for g++ at `-O0`, `-O1` and `-O2` and for clang++ at `-O0` and `-O1`; clang++ at `-O2` reports `heap-use-after-free`. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Do not rely on lambda captures across suspension: pass the data as a by-value coroutine parameter (as in `good.cpp`, which copies it into the frame), or keep the closure object alive until the coroutine completes. The fixed program prints the string.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

