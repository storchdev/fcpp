# 035.01 — Range-based `for` over temporary objects: C++20

## Why the bad code is wrong (`bad.cpp`)

The range-based `for` is defined by cppreference as `{ auto&& range = range-initializer; for (auto begin = …, end = …; begin != end; ++begin) { … } }`. Only the object the range-initializer *produces* is bound to `range`, and so extended. In `make().items()` the expression produces a `const std::vector<std::string>&` that refers into the `Box` returned by `make()`; the `Box` is a temporary created while evaluating the initializer, and before C++23 it is destroyed at the end of that initialization (the semicolon of the `auto&& range = …;` declaration). The loop body then iterates over a vector inside a destroyed `Box`: undefined behavior. Both g++ 16.2.1 and clang++ 23.1.1 with `-std=c++20 -fsanitize=address` report `stack-use-after-scope` (`-O1`).

It is a trap because `for (x : make().items())` reads naturally, and the same loop is fine (scratch program, both compilers, `-std=c++20 -fsanitize=address`) if the accessor returns by value or if the range expression is a function returning the container itself (`for (x : make_vec())` binds the prvalue to `range` and extends it). Only an accessor that returns a reference or view into the temporary is dangerous.

Detection: g++ warns under `-Wall -Wextra`: `warning: possibly dangling reference to a temporary [-Wdangling-reference]`. clang++ did not warn on this code.

## The fix (`good.cpp`)

Name the owner. The C++20 range-for init-statement keeps its scope tight: `for (const Box box = make(); const auto& s : box.items())`. Alternatively make `items()` return by value, or add an `&&`-qualified overload that moves the vector out (entry 022).
