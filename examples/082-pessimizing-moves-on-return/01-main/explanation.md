# 082 — Pessimizing moves on return

## Why the bad code is wrong (`bad.cpp`)

Copy elision for `return b;` (NRVO) applies when the operand is the name of a local object. `std::move(b)` is a function call whose result is an xvalue, not the name of a local, so the object can no longer be constructed directly in the caller's return slot, and a move constructor must run. The program printed `construct` then `move` with both compilers at `-O0` and `-O2`; the fixed `return b;` printed only `construct`.

The value is a performance problem: for a cheap-to-move type it costs a move, for a type without a move constructor it becomes a copy. It is written by people who learned "use `std::move` to avoid copies" and apply it where the language already does the right thing. The fix is the opposite of what the code suggests, which is why it passes review.

Both compilers diagnose it under `-Wall -Wextra` with `-Wpessimizing-move`: "moving a local object in a return statement prevents copy elision" (identical text in g++ and clang++).

## The fix (`good.cpp`)

Return the local by name. The compiler either constructs it in place (NRVO, not guaranteed) or treats the return as an rvalue and moves, never copies. `std::move` on return is needed only when returning something that is not a plain local (a member, a parameter of a different type, or a subobject).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
