# 145 — Concurrent access to standard containers

## Why the bad code is wrong (`bad.cpp`)

The standard guarantees that concurrent calls to `const` member functions are safe, but `push_back` modifies the vector (size, and sometimes reallocation) and conflicts with any other access to it. Two threads pushing at once is a data race, which is undefined behavior. Plain runs of this program show the damage: `size = 1000` instead of 2000 (every g++ and clang++ `-O2` run except two that printed 1824 and 1821), `size = 33557242`, `size = 1824` (g++ `-O0`), and crashes with glibc messages such as `double free or corruption (out)` and `corrupted size vs. prev_size` (both compilers, varying per run).

ThreadSanitizer reports `data race` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Protect every access with a mutex (as in `good.cpp`), partition the data so each thread owns its own container and merge afterwards, or use a concurrent container. The fixed program prints `size = 2000 (expected 2000)`; note that iterators and references are also invalidated by another thread's modification, so locking must cover their whole use.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

