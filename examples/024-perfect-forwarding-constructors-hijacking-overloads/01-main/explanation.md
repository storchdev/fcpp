# 024 — Perfect-forwarding constructors hijacking overloads

## Why the bad code is wrong (`bad.cpp`)

`template <class T> explicit Session(T&&)` is a candidate for every argument. For `Session b(a);` with a non-const lvalue `a`, overload resolution compares `Session(Session&)` (the template with `T = Session&`) against `Session(const Session&)`. The template is an exact match with no qualification added; the copy constructor needs a `const` qualification conversion on the reference binding, so the template wins and `b` is *not* a copy. In `bad.cpp` that gives a fresh id: `a=1 b=2 d=1` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17`). `d`, copied from a `const Session&`, is a real copy (id 1), which hides the bug in tests that copy const objects. The same applies to moves: in a scratch program `Session e(std::move(a));` also called the template (`e=2`).

In the typical real-world version the template body does something with the argument, so the hijack is a compile error instead. With `template <class T> explicit Person(T&& n) : name_(std::forward<T>(n)) {}` and a `std::string name_`, `Person q(p);` fails on both compilers: g++ `no matching function for call to ‘std::__cxx11::basic_string<char>::basic_string(Person&)’`, clang++ `no matching constructor for initialization of 'std::string' (aka 'basic_string<char>')`. The error points into the standard library rather than at the real problem.

No warning fires under `-Wall -Wextra`. Detection: clang-tidy `bugprone-forwarding-reference-overload` reports `constructor accepting a forwarding reference can hide the copy and move constructors` (verified).

## The fix (`good.cpp`)

Constrain the template so it is removed from overload resolution for `Session` (and derived/cv-ref variants): `requires (!std::same_as<std::remove_cvref_t<T>, Session>)` in C++20; before C++20 use `std::enable_if_t<!std::is_same_v<std::decay_t<T>, Session>>`. `good.cpp` then prints `a=1 b=1 d=1`. A tag-dispatch or a named factory is the alternative when the constraint is hard to state.
