# 111 — Hidden friend functions

## Why the bad code is wrong (`bad.cpp`)

A friend function defined inside a class is a member of the enclosing namespace but is not visible to ordinary lookup (qualified or unqualified); it can only be found by ADL, which needs an argument whose associated classes include `Meter`. `inspect(Meter{3})` works. `inspect(3)` does not: `int` has no associated class, so ADL has nothing to search, and the implicit conversion `int -> Meter` is never tried because no candidate exists. Both compilers reject it: g++ "‘inspect’ was not declared in this scope", clang++ "use of undeclared identifier 'inspect'".

It surprises people who expect the function to accept anything convertible to `Meter`. Detection is the compile error.

## The fix (`good.cpp`)

Convert explicitly (`inspect(Meter(3))`), or also declare the function at namespace scope if it must accept convertible arguments. The fixed program prints `3 m` twice.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

