# 103 — `std::remove` vs. container erasure

## Why the bad code is wrong (`bad.cpp`)

`std::remove` works on iterators, not on the container: it moves the elements that are not equal to the value to the front, preserves their order, and returns an iterator to the new logical end. The container is never told, so `size()` is unchanged, and the elements after the new end are in a valid but unspecified state. The program printed `size = 4: 1 3 3 2` with both compilers at `-O0` and `-O2`: the kept elements `1 3` are in front, followed by leftovers.

It is a classic bug because the call looks like "remove 2 from the vector". Here both compilers warn without any extra flags: g++ "ignoring return value of ‘... std::remove(...)’, declared with attribute ‘nodiscard’ [-Wunused-result]" and clang++ "ignoring return value of function declared with 'nodiscard' attribute [-Wunused-result]", because this libstdc++ marks `std::remove` as `nodiscard`. `clang-tidy -checks=bugprone-unused-return-value` reports it too.

## The fix (`good.cpp`)

Use the erase-remove idiom, `v.erase(std::remove(v.begin(), v.end(), 2), v.end())`, or in C++20 `std::erase(v, 2)`; `list::remove` and `list::remove_if` are member functions that do erase. The fixed program prints `size = 2: 1 3`.

## Rust (`good.rs`)

`Vec::retain` removes elements and shrinks the vector in one call; the demo prints `size = 2: [1, 3]`.
