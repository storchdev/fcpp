# 006.01 — Implicit conversion chains: a standard conversion beats a user-defined one

## Why the bad code is wrong (`bad.cpp`)

Overload resolution compares *implicit conversion sequences* for each argument ([over.ics.rank]). A standard conversion sequence is always better than a user-defined conversion sequence, and any user-defined sequence is better than an ellipsis sequence. Which sequence applies depends only on the types, not on which target is the "intended" one.

For `log("disk full")` the argument is a `const char[10]`:

- `log(bool)`: array-to-pointer conversion, then a boolean conversion (pointer to bool). This is a *standard* conversion sequence.
- `log(const std::string&)`: the converting constructor `std::string(const char*)`. This is a *user-defined* conversion sequence.

The standard sequence wins, so the program calls `log(bool)` with `true`. Observed output (g++ 16.2, `-std=c++17`): `bool: 1` and then `string: disk full`. There is no warning with `-Wall -Wextra`. It is a classic trap in logging APIs and in any overload set that has a `bool` parameter next to a class-type parameter such as `std::string`.

Nothing is undefined; the wrong function is simply called.

## The fix (`good.cpp`)

Make the `bool` overload only accept actual `bool`s. Here a constrained template (`std::same_as<bool>`, C++20) removes it from consideration for pointer arguments. Alternatives: add an exact `log(const char*)` overload that forwards to the string version; replace the `bool` parameter with a small enum.

Rust has no overloading and no implicit conversions between these types, so the call chooses exactly one function.
