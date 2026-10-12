# 178 — I/O buffering and unexpected flushing

## Why the bad code is wrong (`bad.cpp`)

`std::endl` writes `'\n'` and then calls `flush()`, which calls `sync()` on the stream buffer; with a real file or terminal that is a system call per line. The program replaces the buffer with one that counts `sync()` calls and printed `flushes = 100000, bytes = 1088890` for 100000 lines with both compilers at `-O0` and `-O2`; the version that writes `'\n'` and flushes once prints `flushes = 1` with the same bytes. I counted flushes rather than timing real I/O, so no wall-clock cost is claimed here.

The code is well-defined and neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Write `'\n'` and flush only when the data must become visible; also consider `std::ios::sync_with_stdio(false)` for `cin`/`cout` throughput (not measured here). The fixed program prints `flushes = 1, bytes = 1088890`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

