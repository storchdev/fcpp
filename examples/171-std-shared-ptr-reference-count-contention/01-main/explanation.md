# 171 — `std::shared_ptr` reference-count contention

## Why the bad code is wrong (`bad.cpp`)

Passing a `shared_ptr` by value copies it: an atomic increment on entry and an atomic decrement on exit, on the same control block in every thread. With four threads each making 5000000 calls, the cache line holding the count bounces between cores. Three runs each took: g++ `-O0` 470–476 ms, g++ `-O2` 429–432 ms, clang++ `-O0` 426–504 ms, clang++ `-O2` 423–427 ms, against 24–25, 5, 27–34 and 5 ms for the version that passes `const Config&`.

There is no data race and neither compiler warns under `-Wall -Wextra`; it shows up in a profiler as atomic operations and cache misses on the control block.

## The fix (`good.cpp`)

Pass `const T&` (or a raw pointer or reference to the object) to functions that only observe, and keep `shared_ptr` copies for actual shared ownership. The fixed program reads the same value through a `const Config&`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

