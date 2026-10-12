# 014.01 — `auto` with brace initialization: copy-list gives `initializer_list`

## Why the bad code is wrong (`bad.cpp`)

For a declaration `auto x = { e1, e2, … }`, deduction treats the initializer as a braced-init-list and deduces `std::initializer_list<T>` where `T` is the common type of the elements. A single element does not change that: `auto a = {42};` is `std::initializer_list<int>`, whereas `auto b{42};` (direct-list-initialization, one element) is `int`. The `static_assert`s in `bad.cpp` check both on g++ 16.2.1 and clang++ 23.1.1.

The two look nearly identical, and the only syntactic difference is the `=`. The program prints `sizeof(a)=16 sizeof(b)=4, a.size()=1` on both compilers (x86-64): `a` is a pointer-and-length view of a backing array, not a number. If such a variable is kept or returned, it refers to a backing array whose lifetime is not the variable's (see entry 030).

Older documentation says `auto x{42};` is also an `initializer_list` in C++11. That was changed by N3922 and applied retroactively as a defect report; cppreference's `auto` page records this. In my tests (both compilers, `-std=c++11`, `-std=c++14`, `-std=c++17`) `auto b1{1};` was `int` in every mode, so code written for either reading behaves the same on current compilers. No warning is produced under `-Wall -Wextra`; detection is by review. (clang-tidy `bugprone-sizeof-container` fired on the `sizeof(a)` in this file, but only because of the demonstration print, not because of the deduction.)

## The fix (`good.cpp`)

For one value, write `auto a = 42;` or `auto b{42};`. If a list is really wanted, name the type: `std::initializer_list<int>{42}`, or better a real container. Avoid `auto x = {…}` unless you specifically want an `initializer_list`.
