# 003 — Brace initialization vs. parentheses

## Why the bad code is wrong (`bad.cpp`)

`T x(args)` is direct-initialization: overload resolution picks a constructor from the argument list. `T x{args}` is direct-*list*-initialization ([dcl.init.list]), which runs overload resolution in two phases ([over.match.list]). Phase one considers only the `std::initializer_list` constructors, with the whole braced list as a single argument. Only if none is viable does phase two consider every constructor with the elements as separate arguments.

`std::vector<int>` and `std::string` both have `initializer_list` constructors, so:

| Written | Meaning |
| --- | --- |
| `vector<int>(3, 7)` | `vector(size_type n, const T& value)`: three sevens |
| `vector<int>{3, 7}` | `vector(initializer_list<int>)`: the two elements 3 and 7 |
| `vector<int>(5)` | five value-initialized ints |
| `vector<int>{5}` | one element, 5 |
| `string(3, 'x')` | `"xxx"` |
| `string{3, 'x'}` | the two characters `'\x03'` and `'x'` (3 is a constant that fits in `char`, so it is not a narrowing conversion) |

The program prints `a.size=3 b.size=2 c.size=5 d.size=1` and `s.size=3 t.size=2` (g++ 16.2.1, `-std=c++17 -O1`). The code compiles without warnings, and each pair differs by one bracket character. It bites hardest in generic code. A template that writes `T t{args...}` instead of `T t(args...)` changes meaning depending on whether `T` has an `initializer_list` constructor, and changing a class's constructors can silently change what existing `{}` call sites do.

Nothing here is undefined; the program is well-defined and does something different from what the author likely meant. There is no sanitizer or warning flag for it, so the defense is to choose the bracket deliberately.

## The fix (`good.cpp`)

Use `()` when you mean "call the constructor that takes these arguments" and `{}` when you mean "these are the elements". Library forwarding functions (`std::make_unique`, `emplace_back`, `std::make_shared`) always use parentheses internally, so `make_unique<vector<int>>(3, 7)` gives three elements. Code that needs `{}` semantics must pass a pre-built `std::initializer_list` or a temporary.

## Rust (`good.rs`)

Rust has no constructor overloading. Elements and "count of a value" are different macro forms, `vec![3, 7]` and `vec![7; 3]`, so the two meanings cannot share a spelling.
