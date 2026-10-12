# 096.02 — Past-the-end iterator invalidation: `erase`

## Why the bad code is wrong (`bad.cpp`)

`erase` invalidates the iterators at and after the erased element, which includes `end()`. After `v.erase(v.begin())` the vector's real `end()` is one element closer, but the cached `last` still holds the old address. The loop therefore reads one slot past the end of the live elements (still inside the vector's allocation) and printed `2 3 4 4` with both compilers at `-O0` and `-O2`: the last `4` is the stale slot.

It is undefined behavior that looks like a duplicate element. AddressSanitizer does not report it because the read is inside the allocated block. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Call `v.end()` after the erase (or in the loop condition). The fixed program prints `2 3 4`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
