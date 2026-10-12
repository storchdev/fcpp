# 081 — Moving from `const` objects

## Why the bad code is wrong (`bad.cpp`)

`std::move(a)` for `const Buffer a` has type `const Buffer&&`. A move constructor takes `Buffer&&`, which cannot bind to a const rvalue (that would let it modify a const object), so overload resolution falls back to `Buffer(const Buffer&)`, which accepts a const rvalue. The program printed `copy` for the const source and `move` for the non-const one, with both compilers at `-O0` and `-O2`.

Nothing is wrong according to the language and neither compiler warns under `-Wall -Wextra`: the code is correct, only slow. With a type that owns a large buffer, the "move" duplicates it. This usually appears when a `const` is added to a local or a parameter later (`const std::string s = ...; return std::move(s);`), and reviewers miss it because `std::move` is still there. `clang-tidy -checks=performance-move-const-arg` reports it: "std::move of the const variable 'a' has no effect; remove std::move() or make the variable non-const".

## The fix (`good.cpp`)

Do not make an object `const` if you intend to move from it, or do not call `std::move` on it. The fixed program prints `move`. If a copy is what is wanted, write the copy and drop the `std::move`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
