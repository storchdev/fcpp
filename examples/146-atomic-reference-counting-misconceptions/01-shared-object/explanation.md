# 146.01 — Atomic reference-counting misconceptions: the shared object

## Why the bad code is wrong (`bad.cpp`)

`shared_ptr` makes the control block's reference counts atomic, so copying and destroying distinct `shared_ptr` objects from several threads is safe. It does nothing for the managed object: two threads incrementing `*p` through their own copies is a data race (undefined behavior). The program printed `*p = 118312` (g++ `-O0`) and `136569` (clang++ `-O0`), and `200000` at `-O2` with both compilers (the optimizer combined the loop's increments, so the plain run hides the bug there).

TSan reports `data race` at `-O0` and `-O1` with both compilers; at `-O2` clang++ reports it and g++ does not (the g++ `-O2` run printed nothing). Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Make the pointee thread-safe: `std::atomic<int>` as in `good.cpp`, or guard it with a mutex. The fixed program prints `*p = 200000 (expected 200000)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

