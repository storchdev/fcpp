# 102.01 — `std::vector<bool>` specialization: `auto` deduces the proxy

## Why the bad code is wrong (`bad.cpp`)

`std::vector<bool>` stores one bit per element, so `operator[]` cannot return `bool&`; it returns a proxy object (`std::vector<bool>::reference`) that reads and writes the bit. `auto first = flags[0]` deduces the proxy, so `first` is not an independent copy: `first = false` writes through to the vector. The program printed `flags[0] = 0 (wanted the original true)` with both compilers at `-O0` and `-O2`.

With a normal `vector<T>`, `auto x = v[0]` is a copy, so the habit transfers badly.  The program is well-defined; neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

State the type: `bool first = flags[0];` copies the value. Prefer `std::vector<char>` or `std::bitset`/`std::deque<bool>` when you need a real container of `bool`. The fixed program prints `flags[0] = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
