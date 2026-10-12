# 115 — Forwarding references and braced initializer lists

## Why the bad code is wrong (`bad.cpp`)

A braced-init-list is not an expression and has no type, so it is a non-deduced context for a parameter of type `T&&`: `T` cannot be deduced from `{1, 2, 3}`, the template is not viable, and the call is ill-formed. g++ reports "no matching function for call to ‘take(<brace-enclosed initializer list>)’"; clang++ "no matching function for call to 'take'".

It bites generic wrappers (`make_unique`, `emplace_back`, `std::function` invoke helpers) that forward to a constructor taking an initializer list. Detection is the compile error.

## The fix (`good.cpp`)

Name the type at the call (`take(std::vector<int>{1, 2, 3})`), give `T` a default (`template <class T = std::vector<int>>`), or add an `std::initializer_list<U>` overload. The fixed program builds and exits 0.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

