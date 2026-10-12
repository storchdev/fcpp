# 149 — False sharing

## Why the bad code is wrong (`bad.cpp`)

The two counters are separate objects updated by separate threads, so there is no data race, but they sit in the same cache line, which has to move between cores on every write. In three runs each, the adjacent version took 414–526 ms (g++ `-O0`), 389–418 ms (g++ `-O2`), 562–587 ms (clang++ `-O0`) and 557–564 ms (clang++ `-O2`) for 50000000 increments per thread, against 76–79, 67–69, 81–83 and 69–70 ms for the padded version on this 32-thread machine.

There is no sanitizer or warning for it under `-Wall -Wextra`; it is found by profiling (cache-miss or contention counters). I did not run a profiler here.

## The fix (`good.cpp`)

Give each hot variable its own cache line with `alignas(64)` (or `std::hardware_destructive_interference_size` from `<new>` where the library provides it; I used 64 literally because I did not verify that constant). The padded program printed times of 67–83 ms in the runs above. The cost is memory, 64 bytes per padded member.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

