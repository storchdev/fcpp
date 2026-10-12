# 083.01 — Copy elision vs. actual moves: named local

## Why the bad code is wrong (`bad.cpp`)

Since C++17 a prvalue initializes its destination directly, so `return Pinned();` does not involve a move or copy constructor at all. `return p;` is different: `p` is a named local (an lvalue), the compiler may apply NRVO but is not required to, and the program must still be well-formed as if the object were moved or copied. With `Pinned(Pinned&&) = delete` that constructor is selected and found deleted, so the program is ill-formed even though a compiler could have elided the move.

Both compilers reject it at `-O0` and `-O2`: g++ "use of deleted function ‘Pinned::Pinned(Pinned&&)’", clang++ "call to deleted constructor of 'Pinned'". Reasoning as if "the move always disappears" is wrong here: the rule for named locals is that the constructor must be accessible even when elision happens.

## The fix (`good.cpp`)

Return a prvalue (`return Pinned();`) so that guaranteed elision applies and no move constructor is needed; the fixed program builds and exits 0. The same applies to a type with a deleted copy and move that must be created by a factory function.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
