# 009 — Integer literal type deduction

## Why the bad code is wrong (`bad.cpp`)

An integer literal has no sign and its type is the *first type in a list that can represent the value* ([lex.icon]). The list depends on the base and suffix:

| Spelling | Candidate types, in order |
| --- | --- |
| decimal, no suffix | `int`, `long`, `long long` |
| octal or hex, no suffix | `int`, `unsigned int`, `long`, `unsigned long`, `long long`, `unsigned long long` |
| decimal with `u` | `unsigned int`, `unsigned long`, `unsigned long long` |

So the *same value* can have a signed or unsigned type depending only on how it is written. A decimal literal never becomes unsigned without a `u` suffix; a hexadecimal one does as soon as it no longer fits in `int`. The program prints (g++ 16.2 and clang++ 23.1, x86-64 Linux, where `long` is 64-bit):

```
2147483647  : int
2147483648  : long
0x80000000  : unsigned int
-2147483648 : long
```

Two consequences cause real bugs:

- **Overload selection and deduction.** `f(2147483648)` and `f(0x80000000)` call different overloads; `auto x = 0x80000000;` is `unsigned int` while `auto y = 2147483648;` is `long`. The exact types also depend on the platform: on a target where `long` is 32-bit (e.g. 64-bit Windows) the decimal literal is `long long`.
- **Mixed-sign comparison.** With `int status = -1;`, `status < 0xFFFFFFFF` compares as `unsigned int`: `status` is converted to 4294967295, and the comparison is false. The decimal spelling `status < 4294967295` compares as `long` and is true. Both conditions look like "is `-1` less than 2^32-1", but only the second prints. Both compilers warn about it under `-Wall -Wextra` (`-Wsign-compare`), which is easy to overlook in a build log.

`-2147483648` is the unary minus operator applied to the literal `2147483648`, which is why it has type `long` and not `int`; this is why `<limits.h>` defines `INT_MIN` as `(-2147483647 - 1)`. Nothing here is undefined behavior: the integral conversions involved are all defined (unsigned conversion is modulo arithmetic).

## The fix (`good.cpp`)

Say the type: use fixed-width types (`std::uint32_t`, `std::int64_t`) and explicit suffixes (`u`, `LL`) on constants whose type matters, and convert operands to a common signed type before comparing. C++20 also provides `std::cmp_less` and friends in `<utility>`, which compare integers of different signedness correctly.

## Rust (`good.rs`)

Rust literals have no value-dependent type. An unsuffixed literal takes its type from context (default `i32`), a literal that does not fit is rejected by the deny-by-default `overflowing_literals` lint (`literal out of range for i32`), and comparing `i32` with `u32` is `error[E0308]: mismatched types`, so you must widen explicitly.
