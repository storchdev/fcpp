# 177 — Clock semantics in latency measurement

## Why the bad code is wrong (`bad.cpp`)

`std::chrono::high_resolution_clock` is the clock with the shortest tick period, but it is not required to be steady. In this standard library it is an alias of `system_clock`: the program printed `high_resolution_clock is steady: 0, same type as system_clock: 1, as steady_clock: 0` with both compilers at `-O0` and `-O2`. `system_clock` follows the wall clock, which can be stepped (NTP, manual changes), so an interval measured with it can be wrong or even negative. A short run like this one printed `elapsed is non-negative here: 1`, which proves nothing.

The code is well-defined. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Measure intervals with `std::chrono::steady_clock`, which is guaranteed monotonic (`is_steady`); use `system_clock` only for calendar timestamps. The fixed program asserts `Clock::is_steady` at compile time and prints `steady_clock is steady: 1, non-negative elapsed: 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

