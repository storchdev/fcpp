# 013 — `auto` drops qualifiers and references

## Why the bad code is wrong (`bad.cpp`)

Plain `auto` follows the template-argument-deduction rules for a by-value parameter (`template<class T> void f(T)`), not the rules for the initializer's own type. The initializer's reference-ness is discarded first, then top-level `const`/`volatile` are discarded. So `auto copy = ref;` where `ref` is `const Particle&` deduces `Particle`: a new, non-const object that is copy-initialized from `ref`. `bad.cpp` proves it with `static_assert(std::is_same_v<decltype(copy), Particle>)`.

Two different symptoms follow from the same rule:

- **Lost writes.** `for (auto p : ps) p.x += 10;` mutates a per-iteration copy; `ps` is untouched. The program prints `1 2` where the author wanted `11 12` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17 -O1`). It compiles without a warning under `-Wall -Wextra` on both compilers.
- **Const quietly disappears.** `copy.x = 99;` compiles even though the source was `const`, because `copy` is a fresh object. This is not a const violation; it is just not the object the author thinks they are editing.

Only the *top-level* qualifiers and the reference are dropped. In a scratch program (both compilers, `-std=c++17`) I confirmed `auto a = pc;` with `const char* const pc` gives `const char*` (pointee const is kept), arrays decay (`auto a = arr;` is `int*`), and functions decay to function pointers. Copying is also the PERF cost: for a type with an expensive copy constructor every iteration pays for it, and nothing in the source says so.

Reviewers miss it because `auto` reads as "the same type as the right-hand side". No warning flag in `-Wall -Wextra` caught `bad.cpp` on either compiler, and none of the clang-tidy performance/bugprone checks I tried flagged this particular code. Detection is by review: look for `auto x = <lvalue>` and `for (auto x : container)` and ask whether a copy is intended.

## The fix (`good.cpp`)

Say what you mean: `const auto&` for read-only access without a copy, `auto&` to mutate in place (`auto&` keeps the object's constness: `auto& r = ci;` is `const int&`, verified with `static_assert`). Use `auto` only when a copy is the intent, and consider writing the type name when it is not obvious. `auto&&` in a range-for is the generic choice when you do not care whether the range yields references or proxies.

## Rust (`good.rs`)

A Rust `let` binds exactly the type of the expression. There is no decay step: `let view = &ps[0];` is `&Particle` (shared, read-only; writing through it is `E0594`), and iterating mutably is spelled `iter_mut()`. Copying a non-`Copy` struct requires an explicit `.clone()`.
