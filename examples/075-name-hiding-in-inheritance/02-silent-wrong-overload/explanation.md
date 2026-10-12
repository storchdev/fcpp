# 075.02 — Name hiding in inheritance: silently selected function

## Why the bad code is wrong (`bad.cpp`)

The same lookup rule as case 01, but here the call still compiles because `1` converts to `double`. `d.f(1)` finds `f` in `Derived`, stops, and picks `Derived::f(double)` even though `Base::f(int)` would be the exact match. Calling through a `Base&` finds `Base::f` instead. Both compilers printed `Derived::f(double)` then `Base::f(int)` at `-O0` and `-O2`.

Nothing warns: neither compiler reported anything under `-Wall -Wextra`, and also not with `-Woverloaded-virtual` or `-Wshadow` added (those concern virtual functions and variables, not hidden non-virtual functions). The behavior changes when someone adds an overload to `Derived` months after the call sites were written: calls that used to reach `Base::f` start converting their arguments and calling the new function.

## The fix (`good.cpp`)

`using Base::f;` in `Derived` puts both overloads in scope, so `d.f(1)` calls `Base::f(int)` (the better match) and `d.f(1.5)` calls `Derived::f(double)`. The fixed program prints `Base::f(int)` then `Derived::f(double)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
