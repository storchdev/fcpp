# 008.02 — Null pointer overload resolution: forwarding loses the null pointer constant

## Why the bad code is wrong (`bad.cpp`)

A literal `0` is a *null pointer constant* only as long as the compiler can see that it is a constant zero. In `new Node(0)` the argument is that literal, so the conversion to `Node*` applies. In `std::make_unique<Node>(0)` the argument is deduced as `int` and forwarded as `int&&`. Inside `make_unique` it is an ordinary `int` object and `int` does not convert to `Node*`.

The compiler rejects it, but with an error from inside the library rather than at your call site. g++ 16.2: `unique_ptr.h:1105:30: error: invalid conversion from 'int' to 'Node*' [-fpermissive]`; clang++ 23.1: `error: no matching constructor for initialization of 'Node'`. The same applies to `NULL` (an integer constant, see 008.01), and to `emplace_back`, `std::make_shared`, and anything else that perfectly forwards its arguments.

## The fix (`good.cpp`)

Pass `nullptr`. `std::nullptr_t` is an actual type, so it deduces and forwards intact, and converts to any pointer at the final call.

## Rust (`good.rs`)

Rust has no null pointer constants and no implicit integer-to-pointer conversion. "Nothing here" is `Option::None` and has to be written at every call site, including through generic functions, so the bug class does not exist (`next: 0` is `E0308`, mismatched types).
