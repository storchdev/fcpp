# 035.02 — Range-based `for` over temporary objects: C++23, and the hoisted reference

## Why the bad code is wrong (`bad.cpp`)

C++23 changed the range-for: cppreference notes the code is equivalent to the expansion "except for the lifetime expansion of temporaries of range-initializer (since C++23)". Under `-std=c++23` the loop from case 01, `for (const auto& s : make().items())`, is fine on both compilers: I compiled it with g++ 16.2.1 and clang++ 23.1.1 with `-fsanitize=address` and it printed both strings with no report.

The extension is a property of the range-for *statement*. `auto&& r = make().items();` is an ordinary reference declaration with an initializer that calls a member function on a temporary, which is the case from entry 026: the `Box` dies at the semicolon even in C++23. The loop `for (const auto& s : r)` then iterates a dangling reference. Both compilers with `-std=c++23 -fsanitize=address` report `stack-use-after-scope`; g++ also warns `[-Wdangling-reference]`. The refactor "pull the initializer into a variable for readability" silently changes a safe loop into an unsafe one.

Code that must also build as C++20 gets case 01's behavior for the original loop.

## The fix (`good.cpp`)

Keep the `Box` in a named variable (`const Box box = make();`) for as long as any reference into it is used, or leave the full expression inside the range-for.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
