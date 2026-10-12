# 102.02 — `std::vector<bool>` specialization: no `bool&`

## Why the bad code is wrong (`bad.cpp`)

Dereferencing a `vector<bool>` iterator yields a proxy prvalue, not an lvalue `bool`. `for (auto& b : v)` tries to bind a non-const lvalue reference to that temporary, which is ill-formed, so generic code that works for every other `vector<T>` fails to compile. Both compilers reject it at `-O0` and `-O2`: g++ "cannot bind non-const lvalue reference of type ‘std::_Bit_reference&’ to an rvalue of type ‘std::_Bit_iterator::reference’", clang++ "non-const lvalue reference to type 'reference' (aka '_Bit_reference') cannot bind to a temporary of type 'reference' (aka '_Bit_reference')".

The error shows up in templates instantiated with `bool`, far from the cause, and the message names library-internal types.

## The fix (`good.cpp`)

Use `auto&&` (a forwarding reference binds to the proxy or to `bool&`), which is also how generic code should iterate. The fixed program builds and exits 0.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
