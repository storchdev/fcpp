# 015.01 — `decltype` vs. `decltype(auto)`: `auto` strips the reference

## Why the bad code is wrong (`bad.cpp`)

`template <class C> auto at(C& c, std::size_t i) { return c[i]; }` has a deduced return type, which follows by-value template deduction: `c[i]` is an lvalue of type `Cell`, so the return type is `Cell` and a copy is returned. `at(cells, 0).bump()` then bumps a temporary and the program prints `cells[0].n = 0` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17`).

The method call is deliberate. The more obvious `at(cells, 0).n = 5;` is *ill-formed* here, so the compiler rescues the author: g++ says `using rvalue as lvalue`, clang++ says `expression is not assignable` (I tried it). It is only through a member function (or a user-defined `operator=`) on the returned class prvalue that the code compiles and silently does the wrong thing. The same shape appears in generic wrappers, forwarding accessors and "transparent" proxies that are supposed to behave like `operator[]`.

No warning appears under `-Wall -Wextra` on either compiler and no sanitizer applies; detection is by reviewing the return type of forwarding wrappers.

## The fix (`good.cpp`)

`decltype(auto)` makes the deduced return type `decltype(c[i])`, i.e. `Cell&`; `good.cpp` checks that with `static_assert`. Alternatives: a trailing return type `-> decltype(c[i])` (C++11), or spell the return type (`-> typename C::reference`). Remember the converse hazard in case 02.

## Rust (`good.rs`)

Return types are always written out, so there is nothing to decay; `fn at(c: &mut [Cell], i: usize) -> &mut Cell` states the reference and the borrow checker ties its lifetime to `c`.
