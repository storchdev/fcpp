# 113 — SFINAE vs. hard compilation errors

## Why the bad code is wrong (`bad.cpp`)

Substitution failure is not an error only for failures in the immediate context of the function declaration (parameter types, return type, template-parameter defaults). `describe` has a deduced return type, so to know whether the overload is viable the compiler must instantiate its body, and `t.size()` on an `int` fails there: a hard error, not a discarded candidate. The fallback `describe(...)` is never reached. g++ prints "In instantiation of ‘auto describe(const T&) [with T = int]’" with "request for member ‘size’ in ‘t’, which is of non-class type ‘const int’"; clang++ prints "member reference base type 'const int' is not a structure or union" with a note "in instantiation of function template specialization 'describe<int>'".

The error message points into the template body rather than at the call site's overload set, which is the clue. Detection is the compile error.

## The fix (`good.cpp`)

Put the check in the signature (`-> decltype(t.size())`, or a `requires` clause in C++20) so the failure happens during substitution. The fixed program prints `-1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

