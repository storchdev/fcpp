# 156 — Coroutine handle ownership

## Why the bad code is wrong (`bad.cpp`)

`std::coroutine_handle` is a non-owning, trivially copyable pointer to the coroutine frame; something else must call `destroy()` exactly once. Here the `Task` destructor owns the frame, and `main` also calls `t.h.destroy()`, so the frame is destroyed twice: undefined behavior. Plain runs at `-O0` with both compilers and at `-O2` with g++ aborted (`timeout: the monitored command dumped core`); at `-O2` clang++ printed `running` and exited normally.

AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` for g++ and at `-O0` for clang++; clang++ at `-O1` and `-O2` reports nothing (I did not investigate why). Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Give the frame a single owner (RAII `Task` with a move-only handle, as in `good.cpp`) and never call `destroy()` through a copy of the handle. The fixed program prints `running` and exits 0.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

