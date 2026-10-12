# 091 — Self-move and aliasing in assignment

## Why the bad code is wrong (`bad.cpp`)

`dst = std::move(src)` is fine when the two are different objects. If both names refer to the same object (here through a generic `assign` helper, but also `v[i] = std::move(v[j])` with `i == j`, or a swap implemented with moves), the move assignment operator runs with `&o == this`. `Buffer::operator=` first deletes its own array, then takes `o.data` (the pointer it just freed, now itself) and sets `o.data = nullptr`, so the object ends with a null `data` and its contents are lost. The program printed `Buffer: data is null` and, for `std::vector`, `vector: size=0` with both compilers at `-O0` and `-O2`.

Here nothing is undefined (the pointer is freed once and then nulled), so no sanitizer reports it; the result is silent data loss. For standard-library types a self-move leaves the object valid but unspecified: both compilers use libstdc++ here, and it emptied the vector. Do not read "emptied" as a guarantee. The aliasing is rarely visible at the call site, which is why reviewers miss it; the direct form `v = std::move(v)` is warned about (`-Wself-move`, both compilers, under `-Wall -Wextra`), but not through the helper.

## The fix (`good.cpp`)

Make the move assignment safe for self-assignment: guard with `if (this != &o)`, or implement it so that aliasing is harmless (swap `data` with `o.data`, or the copy-and-swap idiom). The fixed program prints `Buffer: data is set`.

## Rust (`good.rs`)

Two `&mut` references to the same object cannot coexist: `assign(&mut b, &mut b)` is rejected with `E0499` ("cannot borrow `b` as mutable more than once at a time"), so the aliasing case cannot be written. The demo moves the contents with `std::mem::take` and prints `a=[1, 2, 3] b=[]`.
