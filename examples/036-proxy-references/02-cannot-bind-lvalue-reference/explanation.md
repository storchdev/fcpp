# 036.02 — Proxy references: no lvalue reference to the element

## Why the bad code is wrong (`bad.cpp`)

For `std::vector<bool>`, dereferencing an iterator and `operator[]` return the proxy by value (a prvalue). A non-const lvalue reference cannot bind to a prvalue, so `for (auto& f : flags)` is ill-formed, as are `bool& r = flags[0];` (g++ `cannot bind non-const lvalue reference of type ‘bool&’ to an rvalue of type ‘bool’`) and `auto& r = flags[0];` (both compilers, scratch program). The diagnostics:

- g++ 16.2.1: `error: cannot bind non-const lvalue reference of type ‘std::_Bit_reference&’ to an rvalue of type ‘std::_Bit_iterator::reference’`
- clang++ 23.1.1: `error: non-const lvalue reference to type 'reference' (aka '_Bit_reference') cannot bind to a temporary of type 'reference' (aka '_Bit_reference')`

The error is the same loop that works for every other `std::vector<T>`, which is what makes it confusing; generic code instantiated with `bool` fails here. Detection is the compile error.

## The fix (`good.cpp`)

`for (auto&& f : flags)` binds either a real `T&` or the proxy and works for any element type; assigning through the proxy writes the bit. That form is the standard idiom for generic range-for loops. Do not write `std::vector<bool>::reference` by hand.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
