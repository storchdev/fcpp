# 020.02 — Incorrect `std::forward` usage: the wrong template argument

## Why the bad code is wrong (`bad.cpp`)

`std::forward<X>(u)` casts `u` to `X&&` if `X` is not an lvalue reference. In `Slot<T>::set`, the forwarding reference is `U&&`, and `U` — not the class's `T` — carries the value category of the caller's argument. Writing `std::forward<T>(u)` with `Slot<std::string>` always casts to `std::string&&`, so an lvalue passed by the caller is treated as an rvalue and moved from. `bad.cpp` prints `name size after set: 0` on g++ 16.2.1 and clang++ 23.1.1 (libstdc++), where the caller's string was 45 characters.

The code compiles without warnings under `-Wall -Wextra`. When `U == T` for rvalue calls everything works; only lvalue calls misbehave, so a unit test that passes temporaries misses it. No clang-tidy check I ran detected it, so `detection` is `none`; a reviewer should check that the argument of every `std::forward` is the type of *that* forwarding reference (or write `decltype(u)`), and that the template parameter named in `std::forward<…>` matches the `X&&` it forwards.

## The fix (`good.cpp`)

`std::forward<U>(u)`. Alternatively `std::forward<decltype(u)>(u)`, which cannot name the wrong template parameter.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
