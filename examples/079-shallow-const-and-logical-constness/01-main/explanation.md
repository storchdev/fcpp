# 079 — Shallow `const` and logical constness

## Why the bad code is wrong (`bad.cpp`)

A `const` member function makes `*this` const, which makes each data member const *as a member*: `int* count` becomes `int* const`, a constant pointer to a modifiable `int`. The pointee is a different object and is not affected. So `++*count` in a `const` function is legal, as is `++*owned` (`std::unique_ptr::operator*` is a const member function returning `T&`) and `++*s` for each pointer stored in a `const std::vector<int*>`. `view.bump()` through a `const Counter&` changed all three: the program printed `shared=1 owned=1 a=1` with both compilers at `-O0` and `-O2`.

Nothing is undefined; the type system simply gives `const` a shallow meaning. The footgun is the reader's: the signature promises "does not modify the object", callers pass `const&` to other threads or cache results on that basis, and the object's logical state (everything reachable through its members) changes anyway. Neither compiler warns under `-Wall -Wextra`, and no sanitizer reports it.

## The fix (`good.cpp`)

Make `bump()` non-const, since it mutates, and keep `const` for operations that really only read (`read()`). If a pointee must be modifiable from a const method, make that explicit with `mutable`, an atomic, or a mutex, and document it. Wrappers with deep const (a value member, `std::vector<int>` instead of `std::vector<int*>`, or a `propagate_const`-style pointer wrapper) make `const` mean what the signature says.

## Rust (`good.rs`)

`&self` gives shared access only: `*self.count += 1` through a `&mut i32` field is rejected with `E0594` ("cannot assign to `*self.count`, which is behind a `&` reference"). Mutation from `&self` needs an explicit interior-mutability type such as `Cell`, so it is visible in the field's type; the demo prints `shared = 1`.
