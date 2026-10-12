# 105 — Returning references from `std::min` and `std::max`

## Why the bad code is wrong (`bad.cpp`)

`std::max(const T&, const T&)` returns a reference to one of its arguments. The two `std::string` temporaries are destroyed at the end of the full-expression, so `longest` dangles, and `longest.c_str()` is a use after the object's lifetime. Reference lifetime extension does not apply because the reference is bound to the function's return value, not to a temporary directly.

A plain run printed `banana` with both compilers at `-O0` and `-O2`, because the strings' storage still holds the old bytes. AddressSanitizer reports `stack-use-after-scope` at `-O0`, `-O1` and `-O2` with both compilers. g++ also warns under `-Wall -Wextra`: `-Wdangling-reference` ("possibly dangling reference to a temporary") at `-O0` and `-O2`, plus `-Wdangling-pointer=` at `-O2`; clang++ gave no warning.

## The fix (`good.cpp`)

Copy the result into a value in the same full-expression: `const std::string longest = std::max(...)`. This costs a copy (or a move of an rvalue); binding a `const T&` to the result is only safe when the arguments are objects that outlive the reference. The fixed program prints `banana`.

## Rust (`good.rs`)

`std::cmp::max` takes and returns values, so there is no reference to a destroyed temporary; the demo prints `banana`.
