# 083.02 — Copy elision vs. actual moves: two candidate locals

## Why the bad code is wrong (`bad.cpp`)

NRVO is permitted only where the compiler can construct the returned object in the caller's slot. In `pick`, two locals `a` and `b` are alive at the same time and either may be returned, so at most one of them can live in the return slot, and the other return must run `Tracked(Tracked&&)`. The program printed `construct 1`, `construct 2`, `move 1`, `got 1` with both compilers at `-O0` and `-O2`: both locals were built, and the returned one was moved.

Nothing is wrong with the language rules; the trap is writing code that depends on an elision. The constructor's side effect (here a print) runs in this case and not in the prvalue case, and C++17 does not make the named case guaranteed. Neither compiler warns under `-Wall -Wextra`, and no tool reported it.

## The fix (`good.cpp`)

If side effects or cost matter, return prvalues (`return first ? Tracked(1) : Tracked(2);`), which have guaranteed elision, so only one object is built and no move runs. The fixed program printed `construct 1`, `got 1`. Otherwise keep the named-local code and make the move constructor cheap and free of observable effects.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
