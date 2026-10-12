# 016 — Parentheses changing `decltype` results

## Why the bad code is wrong (`bad.cpp`)

`decltype` has two behaviors. If the operand is an unparenthesized id-expression or an unparenthesized class member access, it yields the *declared type of the entity* (cppreference: `decltype ( entity )`). For any other expression it yields a type that encodes value category: `T&` for an lvalue, `T&&` for an xvalue, `T` for a prvalue. A parenthesized name is an expression, not an entity, so `decltype((cfg.limit))` is `int&` while `decltype(cfg.limit)` is `int`. `bad.cpp` checks both with `static_assert` on g++ 16.2.1 and clang++ 23.1.1.

Here `using Snapshot = decltype((cfg.limit));` makes `Snapshot` an alias for `int&`. `Snapshot before = cfg.limit;` therefore binds a reference, `cfg.limit = 99;` changes what `before` sees, and the program prints `before = 99` instead of `10`. Parentheses sneak in through macros (`TYPEOF((x))`), copy-paste, and formatters, and they are semantically significant only here; in other positions they are invisible.

A second place the same rule shows up: inside a `const` member function, `decltype(m)` for a member `int m` is `int` but `decltype((m))` is `const int&`, since `m` is accessed through `const this`. I confirmed that with `static_assert` in a scratch program on both compilers.

No `-Wall -Wextra` warning fires, and no sanitizer applies. clang-tidy's `readability-redundant-parentheses` reports both parenthesized operands in `bad.cpp`, which is an accidental catch (the check is about style) but removing the parentheses is the correct fix.

## The fix (`good.cpp`)

Write `decltype(cfg.limit)` when you want the member's declared type. If you use the expression form on purpose, strip the reference explicitly (`std::remove_reference_t<decltype((cfg.limit))>`) so the intent is visible; for a snapshot, `auto before = cfg.limit;` is simplest.

## Rust (`good.rs`)

There is no `decltype`; a `let` of a `Copy` field is a copy and a reference exists only if you write `&`. There is no equivalent of an accidental type-level parenthesis.
