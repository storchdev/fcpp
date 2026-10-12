# 030 — `std::initializer_list` backing-array lifetime

## Why the bad code is wrong (`bad.cpp`)

A braced list that initializes an `std::initializer_list<T>` parameter creates a hidden temporary array of `const T`; the `initializer_list` object is only a pointer and a length referring to it. That array has the lifetime of the temporary created for the call, i.e. it ends at the end of the full-expression `Samples s{argc, argc + 1, argc + 2};`. The constructor copies the `initializer_list` into the member, which copies the pointer and size, not the elements, and copying a list does not extend the array. `*s.values.begin()` in the next statement reads the dead array: undefined behavior.

g++ 16.2.1 reports `stack-use-after-scope` with `-fsanitize=address -O1` (`-std=c++17`). clang++ 23.1.1 reports it at `-O0` but printed `1` without a report at `-O1`, so use `-O0` there. The elements are runtime values (`argc + n`); with compile-time constant elements, a scratch program that stored the list in a member did not trigger an ASan report on either compiler even though it is equally invalid (I did not investigate why; the array may have been placed in static storage).

Returning a list is the same bug: `std::initializer_list<int> f() { return {1, 2, 3}; }` compiles with a warning on both compilers (g++ `returning temporary ‘initializer_list’ does not extend the lifetime of the underlying array [-Winit-list-lifetime]`, clang++ `returning address of local temporary object [-Wreturn-stack-address]`) and, with constant elements, happened to print the right values in my run: it works by accident of where the array was placed.

No `-Wall -Wextra` warning fires for the member-storing form on either compiler, and no clang-tidy check I ran reported it.

## The fix (`good.cpp`)

Copy the elements into an owning container (`std::vector<int>`). Use `std::initializer_list` for parameters only, and consume it before the call returns.
