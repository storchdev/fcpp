# 046 — Union type punning

## Why the bad code is wrong (`bad.cpp`)

At most one member of a union is active (its lifetime has begun). `b.f = 1.0f;` makes `f` active; reading `b.u` reads an inactive member, which is undefined behavior in C++ (C allows it; C++ does not, and `std::bit_cast`/`memcpy` exist for this). Both compilers print the expected `3f800000` at `-O0` and `-O2` (g++ 16.2.1 and clang++ 23.1.1, `-std=c++17`), because they accept the pattern as an extension, which is why it survives in codebases. That is observed behavior, not a guarantee from the standard, and I make no claim about other compilers or flags.

No warning under `-Wall -Wextra`. clang-tidy `cppcoreguidelines-pro-type-union-access` reports `do not access members of unions` on both the write and the read; it flags all union member accesses, including legitimate tagged-union code.

## The fix (`good.cpp`)

`std::bit_cast<std::uint32_t>(1.0f)` (C++20), or `std::memcpy` before C++20. It requires equal sizes and trivially copyable types, which the compiler checks.

## Rust (`good.rs`)

`f32::to_bits()` / `from_bits()` are the safe way. Reading a `union` field in Rust requires `unsafe` and a valid bit pattern for the field type.
