# 096.01 — Past-the-end iterator invalidation: `push_back`

## Why the bad code is wrong (`bad.cpp`)

`end()` is an iterator like any other: when `push_back` reallocates, every iterator including the past-the-end one is invalidated. The loop compares `it` against the cached `end` taken before the reallocation, and also continues with an `it` that points into the old block, so both are dangling.

A plain run printed `visited = 3` with both compilers at `-O0` and `-O2`, which looks right because the freed block's contents are still there. AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both compilers. The pattern is common as "hoisting `end()` out of the loop for speed", which is only legal if the loop body cannot invalidate it. Neither compiler warns under `-Wall -Wextra`. (`shrink_to_fit` is a non-binding request; it is there so that the `push_back` reallocates.)

## The fix (`good.cpp`)

Re-evaluate `size()`/`end()` each iteration when the body can modify the container, or index. Do not mutate while iterating when avoidable. The fixed program prints `visited = 4`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
