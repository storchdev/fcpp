# 102.03 — `std::vector<bool>` specialization: adjacent elements race

## Why the bad code is wrong (`bad.cpp`)

The memory model guarantees that distinct objects are distinct memory locations, so two threads may write `v[0]` and `v[1]` of a `std::vector<int>` without synchronization. For `vector<bool>` the elements are bits packed into words, so `v[0]` and `v[1]` share the same word, and each write is a read-modify-write of that word: two threads writing different elements race on the word, which is a data race and undefined behavior.

ThreadSanitizer reports `data race` at `-O0`, `-O1` and `-O2` with both compilers. A plain run printed `11` at `-O0` and `-O2`, so the lost update did not show on this run (a race "works" until it does not). Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use a container with real elements, such as `std::vector<char>` (or `std::vector<std::atomic<bool>>`/a mutex when the same element is shared). The fixed program prints `11` and TSan has nothing to report for it.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
