# 128 — Exception guarantees and partially modified state

## Why the bad code is wrong (`bad.cpp`)

`apply` modifies `a.owner` first, then an operation throws before `++a.version`. A function that does not roll back offers only the basic guarantee at best (no leaks, object still valid) and here not even a meaningful invariant: the program printed `owner = bob, version = 0 (owner changed but version did not)` with both compilers at `-O0` and `-O2`. Caller code that catches the exception and continues sees a state that matches neither the old nor the new values.

Nothing is undefined and neither compiler warns under `-Wall -Wextra`; the bug is the missing rollback, found only by reasoning about every throwing call between two writes.

## The fix (`good.cpp`)

Offer the strong guarantee with copy-and-swap: do all fallible work on a copy and commit with a non-throwing move or swap at the end. The fixed program prints `owner = alice, version = 0` after the failed `apply`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

