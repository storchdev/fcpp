# 019.01 — Forwarding references vs. rvalue references: `std::move` on a forwarding reference

## Why the bad code is wrong (`bad.cpp`)

`template <class T> void log(T&& line)` declares a forwarding reference: `log(msg)` with an lvalue `std::string msg` deduces `T = std::string&`, and `line` is `std::string&`. The author read `T&&` as "an rvalue reference, so I may move from it" and wrote `std::move(line)`. `std::move` is an unconditional cast to `T&&`, so the lvalue caller's string is moved into the vector. `bad.cpp` prints `msg="" (size 0)` (g++ 16.2.1 and clang++ 23.1.1, libstdc++); the moved-from string is "valid but unspecified", which libstdc++ implements as empty. Defined behavior, surprising result.

It compiles cleanly without warnings under `-Wall -Wextra`, and each call site looks harmless; the damage is at the caller, which cannot see that `log` moves. Detection: clang-tidy `bugprone-move-forwarding-reference` reports `forwarding reference passed to std::move(), which may unexpectedly cause lvalues to be moved; use std::forward() instead` (verified).

## The fix (`good.cpp`)

`std::forward<T>(line)` casts to `T&&`, which is an lvalue reference for lvalue arguments (copies) and an rvalue reference for rvalues (moves). If the function should only take ownership, write two overloads (`const T&` and `T&&` of a non-template `T`), or take the parameter by value and `std::move` it.
