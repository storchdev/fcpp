# 065 — Function argument evaluation order

## Why the bad code is wrong (`bad.cpp`)

The initialization of function parameters is indeterminately sequenced: all the side effects of evaluating one argument complete before another argument's evaluation starts, but the standard does not say which argument goes first. It is unspecified, not undefined: each `next()` runs exactly once, atomically with respect to the other, but `show(next(), next())` may print `a = 1, b = 2` or `a = 2, b = 1`.

The two compilers disagree on this machine. g++ printed `a = 2, b = 1` and clang++ printed `a = 1, b = 2`, at both `-O0` and `-O2`. Code tested only with clang++ looks left-to-right and breaks when built with g++, and the reverse; the order is also free to change between compiler versions.

No warning appeared from either compiler under `-Wall -Wextra`, and no sanitizer applies, so detection is review: any call whose arguments have side effects, or depend on shared state touched by another argument, should be suspect.

## The fix (`good.cpp`)

Evaluate the arguments into named variables in separate statements, in the order you need. A statement boundary is the only thing that fixes the order for function arguments. (C++17 added ordering rules for assignment, `<<`, `>>`, `&&`, `||` and `,`, but none for function arguments.)

## Rust (`good.rs`)

Rust evaluates function arguments in the order they are written and the language guarantees it; the demo prints `a = 1, b = 2` every time.
