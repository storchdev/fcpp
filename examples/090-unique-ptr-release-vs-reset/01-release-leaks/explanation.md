# 090.01 — `unique_ptr::release` vs. `reset`: `release` leaks

## Why the bad code is wrong (`bad.cpp`)

`release()` sets the `unique_ptr` to null and returns the raw pointer without deleting it; the caller is now responsible for it. Discarding the returned pointer abandons the only reference to the object, so it is leaked and its destructor never runs. The program printed `use() returned; no ~Resource was printed` with both compilers at `-O0` and `-O2`. The program is well-defined, only wasteful.

The name `release` suggests "release the resource", which is what `reset()` does. The leak does not affect the visible result of the program, so only tooling finds it.

g++'s LeakSanitizer reports `Direct leak of 32 byte(s)` at `-O0`, `-O1` and `-O2`; clang++'s reported it only at `-O0` (see `compilers.md`). `clang-tidy -checks=bugprone-unused-return-value` reports the discarded result: "the value returned by this function should not be disregarded; neglecting it may lead to errors". Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `reset()` to destroy now, or simply let the `unique_ptr` go out of scope. Call `release()` only to hand the pointer to something that takes ownership (a C API, another owner), and use its return value. The fixed program prints `~Resource` before `use() returned`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
