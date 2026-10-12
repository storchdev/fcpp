# 104.01 — Algorithms with invalid ranges or iterators: `copy` into a too-small destination

## Why the bad code is wrong (`bad.cpp`)

`std::copy` writes `last - first` elements starting at `d_first` and never checks the destination: `dst` has two elements, the call writes four, so two elements are written past the end of its allocation, which is undefined behavior. A plain run printed `dst[0] = 1` and exited normally with both compilers at `-O0` and `-O2`.

AddressSanitizer reports `heap-buffer-overflow` at `-O0`, `-O1` and `-O2` with both compilers. g++ additionally warned at `-O2` only: `-Warray-bounds=` ("forming offset [8, 15] is out of the bounds [0, 8]" inside `stl_algobase.h`); clang++ did not warn. It is a very common mistake because the algorithms look like they "assign the result" to a container.

## The fix (`good.cpp`)

Insert instead of overwrite: `std::back_inserter(dst)` grows `dst` as it goes (or size the destination first, `dst.resize(src.size())`, or construct it from the range). The fixed program prints `dst.size() = 4`.

## Rust (`good.rs`)

Slice operations are bounds-checked: `copy_from_slice` panics with "copy_from_slice: source slice length (4) does not match destination slice length (2)" on a length mismatch instead of writing out of bounds. The demo copies a matching prefix and extends a `Vec`.
