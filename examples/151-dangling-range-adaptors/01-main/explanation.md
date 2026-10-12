# 151 — Dangling range adaptors

## Why the bad code is wrong (`bad.cpp`)

`v | views::transform(f)` produces a view that refers to `v` without owning it. Returning that view from the function that owns `v` leaves the view pointing at a destroyed vector: reading through it is undefined behavior. Plain runs printed garbage (`first = -1001326794` at g++ `-O0`, `-367847040` at g++ `-O2`; clang++ `-O0` `642637152`, and clang++ `-O2` printed nothing and exited with status 232).

AddressSanitizer reports `stack-use-after-return` for g++ at `-O0`, `-O1` and `-O2` and for clang++ at `-O0`; clang++ reports `heap-use-after-free` at `-O1` and nothing at `-O2`. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Return the data, not a view of local data: materialize into a container (as in `good.cpp`), or let the caller own the source and pass it in. The fixed program prints `first = 2`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

