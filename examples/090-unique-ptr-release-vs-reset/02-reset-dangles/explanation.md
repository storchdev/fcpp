# 090.02 — `unique_ptr::release` vs. `reset`: `reset` dangles

## Why the bad code is wrong (`bad.cpp`)

`reset()` deletes the owned object. `raw` was taken with `get()`, which does not transfer ownership, so after `p.reset()` it points to freed memory and `raw->level` is a use after free, which is undefined behavior. The plain run printed garbage (different on each run) with both compilers at `-O0` and `-O2`, and exit status 0.

The difference between the two operations is the point: `release()` keeps the object alive and gives the pointer to the caller, `reset()` destroys it. Code converted from one to the other, or from a raw owner, reads a pointer it expects to be valid.

AddressSanitizer reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both compilers. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

If the caller needs the object after the `unique_ptr` lets go, use `release()` and take on deletion (or hand the pointer to a new owner such as another `unique_ptr`). Otherwise do not keep a raw pointer past the `reset()`. The fixed program prints `level = 3`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
