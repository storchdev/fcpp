# 076.02 — Multiple inheritance pointer adjustments: round trip through `void*`

## Why the bad code is wrong (`bad.cpp`)

A `void*` holds an address and no type. Converting `void*` back with `static_cast` yields a pointer to the original object only if the target type is the type of the pointer that was converted to `void*`. Here `user_data = &c` stores the address of the `C` object (which is the address of its `A` subobject), and `callback` casts that to `B*`. The result does not point to a `B`, so reading `b->b` is undefined behavior. The program printed `b->b = 1` (it read `A::a`) with both compilers at `-O0` and `-O2`.

This is the typical shape of C callback APIs with a `void* user_data` registered in one place and decoded in another: each side is individually reasonable, and the mismatch exists only between them. No warning from either compiler under `-Wall -Wextra`; no sanitizer was tried.

## The fix (`good.cpp`)

Convert to the exact type the other side will decode before storing: `B* as_b = &c; user_data = as_b;`. The fixed program prints `b->b = 2`. Better, avoid `void*` with a typed wrapper (a template, `std::function`, or a lambda).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
