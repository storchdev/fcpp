# 146.02 — Atomic reference-counting misconceptions: the `shared_ptr` object

## Why the bad code is wrong (`bad.cpp`)

The thread-safety guarantee covers the control block, not the `shared_ptr` object itself: one thread assigning to `global` while another dereferences it is a data race on the pointer (and on the stored control-block pointer), which is undefined behavior. The plain runs print garbage sums (for example `2953978967` and `891659654`, where the correct values are timing-dependent in any case) rather than failing visibly.

TSan reports `data race` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `std::atomic<std::shared_ptr<T>>` (C++20), or a mutex. The fixed program, with `std::atomic<std::shared_ptr<int>>`, builds with both compilers, exits 0 and TSan reports nothing for it with g++ or clang++ at `-O1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

