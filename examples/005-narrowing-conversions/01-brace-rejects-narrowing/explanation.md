# 005.01 — Narrowing conversions: brace initialization rejects them

## Why the bad code is wrong (`bad.cpp`)

[dcl.init.list] defines a *narrowing conversion* as an implicit conversion that may lose information, for example floating to integer, a wider integer to a narrower one that cannot represent every value, or a constant that does not fit. Inside list-initialization, a narrowing conversion makes the program ill-formed. Here `std::uint8_t level{300}` and `int whole{3.5}` are both narrowing.

Observed diagnostics:

- g++ 16.2: `error: narrowing conversion of '300' from 'int' to 'uint8_t' {aka 'unsigned char'} [-Wnarrowing]`, and the same for `'3.5e+0'` from `double` to `int`.
- clang++ 23.1: `error: constant expression evaluates to 300 which cannot be narrowed to type 'std::uint8_t'` and `error: type 'double' cannot be narrowed to 'int' in initializer list`.

The compilers differ on **non-constant** narrowing. For `int n = 3; char c{n};` I observed clang++ report an error (`non-constant-expression cannot be narrowed from type 'int' to 'char'`), while g++ only emits `warning: narrowing conversion of 'n' from 'int' to 'char' [-Wnarrowing]` and compiles. The standard requires a diagnostic, and g++ chooses a warning for non-constants, so portable code must not depend on either behavior. `-Werror=narrowing` makes g++ strict.

The footgun is not the error itself, which is helpful. It is that code that compiled for years as `int whole = 3.5;` breaks the moment someone "modernizes" it to braces, and that brace-initialization rejects narrowing while every other form (case 02) does not.

## The fix (`good.cpp`)

State the conversion you mean. For a constant, use a value that fits. For a double-to-int conversion use `static_cast<int>` and decide the rounding explicitly (`std::lround` rounds to nearest; a bare cast truncates). Conversions that cannot lose information, such as `uint8_t` to `int`, are allowed in braces.

## Rust (`good.rs`)

Rust has no implicit numeric conversions at all. `let whole: i32 = 3.5;` and assigning an `i64` to an `i32` are both `error[E0308]: mismatched types`, and the out-of-range literal `300` for `u8` is rejected by the deny-by-default `overflowing_literals` lint. The explicit `as` is well-defined: float-to-int saturates, and never invokes UB.
