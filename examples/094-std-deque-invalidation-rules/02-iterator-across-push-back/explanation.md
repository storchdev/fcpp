# 094.02 — `std::deque` invalidation rules: iterator across `push_back`

## Why the bad code is wrong (`bad.cpp`)

`push_back` on a `std::deque` invalidates all iterators but not references to existing elements. `ref` stays valid across the 5000 insertions (a scratch run printed `ref ok 2`), while `it` does not: the iterator is invalid, and ASan reports a use after free when it is advanced.

Both compilers' programs crashed (core dumped) in a plain run at `-O0` and `-O2`. AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both compilers. The surprise for people who know `vector` is that the references are fine: code written for one container's rules is carried to another. Neither compiler warns.

## The fix (`good.cpp`)

Obtain iterators after the last `push_back` (or use indices). References to elements may be kept across `push_back` and `push_front`, but not across other insertions or erasures. The fixed program prints `ref = 2, sum = 12497506`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
