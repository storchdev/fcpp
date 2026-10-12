# 029.02 — `std::span` ownership confusion: a span of a temporary container

## Why the bad code is wrong (`bad.cpp`)

`std::span<const int> view = make();` binds a view to the vector returned by `make()`, which is destroyed at the end of the statement. It compiles because `span`'s range constructor accepts an rvalue range when the element type is `const` (the span cannot be used to modify a temporary). With a mutable element type it is rejected: in a scratch program `std::span<int> s = make();` fails on both compilers (g++: `conversion from ‘std::vector<int>’ to non-scalar type ‘std::span<int>’ requested`; clang++: `no viable conversion from 'std::vector<int>' to 'std::span<int>'`), so the `const` form is the one that lets the bug through. A `const` span parameter in a function call is fine; storing the view is not.

`view[0]` reads freed heap memory: AddressSanitizer reports `heap-use-after-free` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++20 -O1`).

Detection: clang++ warns under `-Wall -Wextra`: `warning: object backing the pointer will be destroyed at the end of the full-expression [-Wdangling-gsl]`; clang-tidy `bugprone-dangling-handle` reports `std::span outlives its value`. g++ 16.2.1 gave no warning.

## The fix (`good.cpp`)

Name the owner (`const std::vector<int> owner = make();`) and create the span from it, with the owner declared in an enclosing scope of every use of the span.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
