# 036.01 — Proxy references: `auto` copies the proxy

## Why the bad code is wrong (`bad.cpp`)

`std::vector<bool>` is specialized to store one bit per element. `operator[]` cannot return a `bool&` to a bit, so it returns a proxy object, `std::vector<bool>::reference`, that remembers the word and bit position and converts to `bool`. `auto before = flags[0];` deduces the proxy type (the `static_assert(!std::is_same_v<decltype(before), bool>)` in `bad.cpp` passes on g++ 16.2.1 and clang++ 23.1.1) and copies the proxy, which still refers to the bit inside the vector. After `flags[0] = true;` reading `before` yields `1`: the program prints `saved flag = 1`, not the `0` that was meant to be saved.

This is defined behavior, just surprising. No warning under `-Wall -Wextra` on either compiler and none of the clang-tidy checks I ran reported it.

The pattern is `auto x = container[i]` in generic code: it copies a value for `std::vector<int>` and a live proxy for `std::vector<bool>`.

## The fix (`good.cpp`)

Convert explicitly when you want a value: `bool before = flags[0];`. In generic code, use `auto&&` to bind either a real reference or a proxy, and `static_cast<bool>` (or the element type) for a snapshot. The more general fix is to avoid `std::vector<bool>` (`std::vector<char>`, `std::bitset`, or `std::deque<bool>`).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
