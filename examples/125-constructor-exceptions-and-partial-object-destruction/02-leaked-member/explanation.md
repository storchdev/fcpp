# 125.02 — Constructor exceptions and partial object destruction: leaked member

## Why the bad code is wrong (`bad.cpp`)

`a` is allocated in the mem-initializer list, then the constructor body throws before `b` is allocated. `~Pair` never runs, and nothing else owns the `int` that `a` points to, so it leaks. The leak is reported by LeakSanitizer (part of ASan on Linux): `Direct leak of 4 byte(s)` allocated in `Pair::Pair(bool)`. The program itself prints `caught: second allocation failed` and exits 0.

Leak detection is sensitive to how the compiler keeps pointers alive, so the construction is in a separate `noinline` function; even so, clang++ reported the leak at `-O0` but not at `-O1` or `-O2` in this run. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `std::unique_ptr<int>` members (or `std::make_unique`): the already-constructed members are destroyed by the unwinding. The fixed program prints `caught: second allocation failed` and ASan reports nothing.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

