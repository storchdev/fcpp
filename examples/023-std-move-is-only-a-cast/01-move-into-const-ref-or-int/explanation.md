# 023.01 — `std::move` is only a cast: the receiver cannot move

## Why the bad code is wrong (`bad.cpp`)

`std::move(s)` produces an xvalue `std::string&&`. Passing it to `void inspect(const std::string&)` binds the reference to the same object; no constructor runs, so no resources move. `s` keeps its 40 bytes (`after inspect: 40 bytes`). For `int m = std::move(n);` the receiving type has no move constructor beyond the trivial copy, so `m` is a copy and `n` still holds 5 (`n=5 m=5`). Both compilers (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`) print this and neither warns under `-Wall -Wextra`.

The mistake is believing `std::move` empties things. A reader will assume `s` is dead after `inspect(std::move(s))`, which is not what the code does. Detection: clang-tidy `performance-move-const-arg` reports both `passing result of std::move() as a const reference argument; no move will actually happen` and `std::move of the variable 'n' of the trivially-copyable type 'int' has no effect; remove std::move()` (verified).

## The fix (`good.cpp`)

Drop the `std::move` when the receiver only reads or copies. Use `std::move` into a by-value parameter or `T&&` overload that takes ownership (`adopt(std::move(s))` — after which `s` is empty on libstdc++, valid but unspecified by the standard). For scalars just copy.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
