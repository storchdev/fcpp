# 014.02 — `auto` with brace initialization: multiple elements

## Why the bad code is wrong (`bad.cpp`)

Two separate rules, both ill-formed (`IF`):

- `auto x{1, 2};` — direct-list-initialization of an `auto` variable requires exactly one element. g++ 16.2.1: `error: direct-list-initialization of ‘auto’ requires exactly one element [-fpermissive]`. It is a permissive error in g++ (accepted with `-fpermissive`); clang++ 23.1.1 has no such switch: `error: initializer for variable 'x' with type 'auto' contains multiple expressions`.
- `auto y = {1, 2.5};` — copy-list-initialization deduces `std::initializer_list<T>`, but the elements must all deduce the same `T`. g++: `unable to deduce ‘std::initializer_list<auto>’ from ‘{1, 2.5e+0}’`; clang++: `deduced conflicting types ('int' vs 'double') for initializer list element type`.

The trap is that `std::vector<int> v{1, 2}` is fine and `auto` looks like it should "just work" with the same braces. The diagnostics are clear, so detection is a compile error on both compilers.

## The fix (`good.cpp`)

Make the elements the same type (`{1.0, 2.5}`) or name the destination type and let the elements convert (`std::vector<double> v{1, 2.5};`).
