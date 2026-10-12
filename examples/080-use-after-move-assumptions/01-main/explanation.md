# 080 — Use-after-move assumptions

## Why the bad code is wrong (`bad.cpp`)

`std::move` only casts to an rvalue reference; the move constructor or assignment that then runs decides what is left behind. For types from the standard library the moved-from object is valid but its value is unspecified (a type may document more, but the code cannot assume it), and for a user-defined class with a defaulted move, each member is moved on its own: a `std::string` member is moved (here it ended up empty), but an `int` member is simply copied and keeps its value. After `send(std::move(m))` the program printed `after move: text size=0 priority=7 pending=1`, so `m.pending()` still reports true and `send(std::move(m))` runs a second time with an empty message.

This is not undefined behavior: every operation on `m` is valid. It is a logic bug, and it is easy to write because the empty string makes it look as if the move "reset" the whole object. Whether a moved-from `std::string` is empty is itself up to the implementation; code that depends on it only works where it happens to hold. Both compilers printed the same output at `-O0` and `-O2`, with no warning under `-Wall -Wextra` (see `compilers.md`). `clang-tidy -checks=bugprone-use-after-move` reports it: "'m' used after it was moved".

## The fix (`good.cpp`)

Treat a moved-from object as only fit for destruction or assignment of a new value: do not read it again unless you reset it first (`m = Message{}`, `clear()`, or assigning a new value). Reassigning is the one operation every moved-from object supports. The fixed program prints `after reset: pending=0`. If a type must have a defined moved-from state, give it a move constructor that sets it (and document it).

## Rust (`good.rs`)

Rust moves are destructive and checked: using `m` after `send(m)` is rejected with `E0382` ("borrow of moved value: `m`"); assigning a fresh value to `m` makes it usable again, which is exactly the C++ fix.
