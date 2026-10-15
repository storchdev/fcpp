# 186 — Unchecked vector indexing

## Why the bad code is wrong (`bad.cpp`)

For this C++11 example, `std::vector::operator[]` requires an index less than `size()`. It does not perform a required bounds check. `samples.size()` is one past the last valid index, so `samples[index]` has undefined behavior. The read reaches beyond the vector's three allocated elements in this example.

An unchecked access may appear to produce a number, abort in a library check, or be changed by optimization. All three kinds of observation occurred in the compiler runs in `compilers.md`; none makes the access valid. AddressSanitizer at `-O1` reported `heap-buffer-overflow` with both compilers. A reviewer can also spot the broken invariant `index < samples.size()`.

## The fix (`good.cpp`)

Use `at()` when an invalid index should be reported: it throws `std::out_of_range`, which this example handles. When an invalid index is expected, an explicit `index < size()` test before `operator[]` is another option.

## Rust (`good.rs`)

Slice `get()` returns `None` for an invalid index. The example handles both `Some` and `None` without an out-of-bounds read.
