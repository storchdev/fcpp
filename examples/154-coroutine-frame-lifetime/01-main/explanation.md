# 154 — Coroutine frame lifetime

## Why the bad code is wrong (`bad.cpp`)

A coroutine's state (frame) is allocated when it is first called and destroyed either by `coroutine_handle::destroy()` or, when `final_suspend` does not suspend (`suspend_never`), automatically when the body finishes. The handle is a non-owning pointer: after the frame is gone, calling `done()` or `resume()` through it is undefined behavior. Here `t.h.resume()` runs the body to completion, the frame is freed, and `t.h.done()` reads freed memory. The plain run printed `running` and `done = 0` with both compilers at `-O0` and `-O2`, which looks fine.

AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` for g++; for clang++ only at `-O0`: at `-O1` and `-O2` it reports nothing and the program prints `running`, `done = 0` (I did not investigate why; frame allocation elision is a possible cause but I did not verify it). Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Make `final_suspend` return `suspend_always` so the frame survives until the owning object destroys it (the `Task` destructor calls `destroy()`), and use the handle only while it is owned. The fixed program prints `running` and `done = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

