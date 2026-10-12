# 019.02 — Forwarding references vs. rvalue references: not every `&&` forwards

## Why the bad code is wrong (`bad.cpp`)

Forwarding-reference deduction applies only to a parameter of exactly the form `T&&` where `T` is a template parameter of the function. `std::vector<T>&&` is an ordinary rvalue reference: `T` is deduced as `std::string` from the vector's element type, and the parameter does not bind lvalues. `consume(names)` is ill-formed. g++ 16.2.1: `error: cannot bind rvalue reference of type ‘std::vector<std::__cxx11::basic_string<char> >&&’ to lvalue of type ‘std::vector<std::__cxx11::basic_string<char> >’`; clang++ 23.1.1: `no matching function for call to 'consume'` with the note `candidate function [with T = std::basic_string<char>] not viable: expects an rvalue for 1st argument`.

Two other spellings I checked in a scratch program are *not* forwarding references and reject an lvalue `std::string s` on both compilers: `const T&&` as a function parameter (g++: `cannot bind rvalue reference of type ‘const std::__cxx11::basic_string<char>&&’ to lvalue of type ‘std::string’`; clang++: `no matching function for call to 'cr'`), and a member `void push(T&&)` of `template <class T> struct Stack` once `T` is already fixed to `std::string` by the class.

Detection is a compile error (the failing form), so it is rarely a silent bug; the silent version is case 01.

## The fix (`good.cpp`)

If the function should accept any value category of one specific type, make the whole parameter a forwarding reference and constrain it: `template <class V> requires same_as<remove_cvref_t<V>, vector<string>> void consume(V&& v)` (C++20), then `std::forward<V>(v)`. Otherwise provide `const std::vector<T>&` and `std::vector<T>&&` overloads, or take by value.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
