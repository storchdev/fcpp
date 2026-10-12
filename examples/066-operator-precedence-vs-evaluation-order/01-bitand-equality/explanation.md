# 066.01 — Operator precedence vs. evaluation order: `&` against `==`

## Why the bad code is wrong (`bad.cpp`)

Precedence and associativity decide how an expression is grouped into operands. In C++ the equality operators bind tighter than the bitwise `&`, so `flags & MASK == 0` groups as `flags & (MASK == 0)`: `MASK == 0` is `false`, i.e. `0`, and `flags & 0` is `0`. The condition is always false, and the program printed `bit 2 is set (wrong)` with both compilers at `-O0` and `-O2`, even though bit 2 of `flags` is clear.

This is a grouping bug, not an evaluation-order one: nothing here is unspecified or undefined. It persists because the line reads naturally as a bit test, and both compilers accept the program.

Both compilers warn under `-Wall -Wextra` with `-Wparentheses` (g++: "suggest parentheses around comparison in operand of ‘&’"; clang++: "& has lower precedence than ==; == will be evaluated first").

## The fix (`good.cpp`)

Parenthesize the bit test: `(flags & MASK) == 0`. Parentheses cost nothing and make the grouping visible to the reader and to the compiler's warning.

## Rust (`good.rs`)

In Rust `&` binds tighter than `==`, so `flags & MASK == 0` already means `(flags & MASK) == 0`; the demo prints `bit 2 is clear`. A bitwise test and a comparison have the intuitive grouping, which is the opposite of C++.
