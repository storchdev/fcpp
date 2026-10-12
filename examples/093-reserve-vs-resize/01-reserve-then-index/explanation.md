# 093.01 — `reserve()` vs. `resize()`: indexing after `reserve`

## Why the bad code is wrong (`bad.cpp`)

`reserve(5)` makes `capacity()` at least 5 but leaves `size()` at 0: no elements exist. `operator[]` requires `n < size()`, so writing `v[i]` is undefined behavior even though the memory is allocated. The program then reports `size = 0` and prints no elements, because `size()` never changed.

What happens depends on the build. In this environment both compilers aborted at `-O0` with libstdc++'s assertion `__n < this->size()` failed (in `stl_vector.h`), but at `-O1` and `-O2` the program ran and printed `size = 0` followed by an empty line, with both compilers. With `-O2 -D_GLIBCXX_ASSERTIONS` both aborted with the same assertion. I did not find out why the assertion is active at `-O0` by default here.

The write itself lands inside the allocation, so AddressSanitizer does not see it (a scratch test with `-fsanitize=address` printed `size=0` and no report). Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use `resize(n)` (or the constructor `std::vector<int> v(5)`) when elements must exist, or `reserve` followed by `push_back`/`emplace_back` when they are to be created one at a time. The fixed program prints `size = 5` and `0 1 4 9 16`. Building with `-D_GLIBCXX_ASSERTIONS` turns the bad access into an abort.

## Rust (`good.rs`)

`Vec::with_capacity(5)` has `len() == 0` and `v[0] = 1` is a bounds-checked panic ("index out of bounds: the len is 0 but the index is 0"), never undefined behavior. The demo resizes first and prints `[0, 1, 4, 9, 16]`.
