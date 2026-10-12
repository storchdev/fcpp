# 021 — Const rvalues and move semantics

## Why the bad code is wrong (`bad.cpp`)

`std::move(x)` is `static_cast<remove_reference_t<decltype(x)>&&>(x)`. For `const Blob original`, that is `const Blob&&` (the `static_assert` in `bad.cpp` checks it). A move constructor takes `Blob&&`, and a `const Blob&&` cannot bind to a non-const rvalue reference because that would discard `const`. The copy constructor `Blob(const Blob&)` can bind to a const rvalue, so overload resolution selects it. The program prints `copy` and `original still holds 40 bytes` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17`).

This is well-defined and compiles without a warning under `-Wall -Wextra`; the cost is a silent copy where a move was written. It tends to appear with `const` locals and with `std::move(member_)` inside a `const` member function. For a move-only type the same code is not a silent copy but an error: in a scratch program `const std::unique_ptr<int> cp; std::unique_ptr<int> q = std::move(cp);` fails on g++ (`use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&)`) and clang++ (`call to deleted constructor of 'std::unique_ptr<int>'`).

Detection: clang-tidy `performance-move-const-arg` reports `std::move of the const variable 'original' has no effect; remove std::move() or make the variable non-const` (verified).

## The fix (`good.cpp`)

Don't make the object `const` if it will be moved from, or drop the `std::move` and accept the copy honestly. The fixed program prints `move` and the source holds 0 bytes afterwards (libstdc++ leaves a moved-from `std::string` empty; the standard only requires it to be valid).

## Rust (`good.rs`)

A move is the default for non-`Copy` values; `let taken = original;` moves whether or not the binding was declared `mut`, and a later use of `original` is `E0382`. A silent copy needs an explicit `.clone()`.
