# 097.01 — Erasing while iterating: `unordered_map`

## Why the bad code is wrong (`bad.cpp`)

`erase(it)` invalidates only `it`, and the loop's `++it` then uses it: the node was freed by `erase`, and advancing needs its `next` pointer, so the loop reads freed memory. That is undefined behavior. The program crashed (core dumped) in a plain run at `-O0` and `-O2` with both compilers, and AddressSanitizer reported `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both.

The same loop written for `std::map` is no safer, but the tool did not see it: in a scratch test the equivalent loop over a `std::map<int,int>` ran to completion with ASan on both compilers (printing `size=5`); I did not investigate why. Do not read a clean sanitizer run as evidence that a map loop is correct.

The associative-container `erase(iterator)` returns the next iterator since C++11, which is the intended way to write this loop. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use the returned iterator (`it = m.erase(it)`) and only `++it` in the other branch; or, in C++20, `std::erase_if(m, pred)`. The fixed program prints `size = 5`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
