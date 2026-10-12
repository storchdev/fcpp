# 022.02 — Reference-qualified member functions: an `&`-only member on a temporary

## Why the bad code is wrong (`bad.cpp`)

`Builder& add(const std::string&) &` says the function may only be called on an lvalue (the implicit object parameter is `Builder&`, which cannot bind to a prvalue). `make_builder().add("y")` calls it on a temporary, and with no `&&` or unqualified overload there is no viable function. g++ 16.2.1: `error: passing ‘Builder’ as ‘this’ argument discards qualifiers [-fpermissive]` (a permissive error: it compiles with `-fpermissive`); clang++ 23.1.1: `error: 'this' argument to member function 'add' is an rvalue, but function has non-const lvalue ref-qualifier`.

The `&` qualifier is the right tool when returning `*this` by reference would dangle if the object is a temporary; the cost is that chained calls on a temporary stop compiling. Detection is the compile error on both compilers.

## The fix (`good.cpp`)

Add an `&&` overload that returns by rvalue reference (`Builder&& add(...) &&`), so a chain begun on a temporary keeps working and the final `str()` or a conversion consumes it. Keep both overloads' bodies in sync (or have one call the other through `std::move(*this)`).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
