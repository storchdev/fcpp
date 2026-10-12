# 152 — Borrowed ranges vs. owning ranges

## Why the bad code is wrong (`bad.cpp`)

A range algorithm called with an rvalue range that is not a `borrowed_range` (such as a `std::vector` temporary) returns `std::ranges::dangling` instead of an iterator, because the iterator would refer to a destroyed object. `dangling` has no `operator*`, so dereferencing the result is ill-formed: the library turns a would-be use-after-free into a compile error.

Both compilers reject the program. g++: `error: no match for ‘operator*’ (operand type is ‘std::ranges::dangling’)`. clang++: `error: indirection requires pointer operand ('borrowed_iterator_t<std::vector<int, std::allocator<int>>>' (aka 'dangling') invalid)`.

## The fix (`good.cpp`)

Keep the range alive in a named variable and call the algorithm on it (as in `good.cpp`); for views over an lvalue the iterators are valid as long as that lvalue is. The fixed program prints `2`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

