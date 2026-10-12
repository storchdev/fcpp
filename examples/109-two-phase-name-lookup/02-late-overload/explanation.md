# 109.02 — Two-phase name lookup: late overload

## Why the bad code is wrong (`bad.cpp`)

For a dependent call such as `f(x)`, unqualified lookup at the template definition finds only the `f` declarations visible at that point; at instantiation only argument-dependent lookup adds more. `f(int)` is declared after the template and `int` has no associated namespaces, so it is never found, and `call(1)` picks `f(double)`. The program printed `f(double)` with both compilers at `-O0` and `-O2`.

There is no diagnostic: the call is valid, just not the one intended. It shows up when a header's templates are included before the overloads they are meant to use. Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it.

## The fix (`good.cpp`)

Declare every overload before the template that calls it. The fixed program prints `f(int)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

