# 018 — Reference collapsing

## Why the bad code is wrong (`bad.cpp`)

C++ forbids references to references, but they arise through typedefs and template arguments. The rule is that a reference to a reference collapses: `T& &`, `T& &&` and `T&& &` all become `T&`; only `T&& &&` stays `T&&`. `bad.cpp` verifies all four with `static_assert` through the aliases `LR = int&` and `RR = int&&` (g++ 16.2.1 and clang++ 23.1.1).

This is how forwarding references work: for `template <class T> void f(T&& x)`, an lvalue argument deduces `T = int&`, so the parameter type `T&&` collapses to `int&`; an rvalue deduces `T = int` and the parameter is `int&&`. The trap is using `T` itself as if it were a value type. `T copy = x;` with `T = int&` is `int& copy = x;`. The "private" copy is the caller's variable, `++copy` increments it, and the program prints `n = 2` rather than `1`. Nothing is diagnosed under `-Wall -Wextra`.

It hides because the code is correct for rvalue arguments (`T = int`, a real copy) and wrong only for lvalue arguments, so tests that pass temporaries succeed. clang-tidy's `cppcoreguidelines-missing-std-forward` reports `forwarding reference parameter 'x' is never forwarded inside the function body` on this function (I ran it); it is a pointer to the misuse rather than a diagnosis of the alias.

## The fix (`good.cpp`)

Strip reference and cv qualifiers before declaring a value: `std::remove_cvref_t<T>` (C++20; `std::decay_t<T>` before, which also decays arrays and functions). If the intent is to forward the argument, use `std::forward<T>(x)` instead of copying.

## Rust (`good.rs`)

Rust has no reference collapsing: `&T` and `&mut T` are distinct types and a generic `T` is never silently a reference to the caller's value. A copy is an explicit `.clone()`.
