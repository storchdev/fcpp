# 142 — `std::thread` destruction semantics

## Why the bad code is wrong (`bad.cpp`)

If a `std::thread` object is destroyed while it is joinable (it owns a running or finished thread that was neither joined nor detached), its destructor calls `std::terminate`. This is defined behavior, not UB: the program aborts. Here `main` returns with `worker` joinable, and the program printed `terminate called without an active exception` and dumped core with both compilers at `-O0` and `-O2` (g++ and clang++ both link libstdc++, so the message is the same).

It is easy to hit when an early return or an exception skips the `join()` call. Neither compiler warns under `-Wall -Wextra`, and no sanitizer is involved.

## The fix (`good.cpp`)

Use an RAII wrapper: `std::jthread` (C++20) joins in its destructor. Before C++20, write a small guard that joins in its destructor. The fixed program prints `main returning` and `working` (in that order in the runs I did, though the thread's output order is not guaranteed) and exits 0.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

