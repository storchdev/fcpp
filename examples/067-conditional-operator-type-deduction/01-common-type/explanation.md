# 067.01 — Conditional operator type deduction: common type of the branches

## Why the bad code is wrong (`bad.cpp`)

The second and third operands of `?:` are not required to have the same type. When they differ and are arithmetic, the usual arithmetic conversions bring them to a common type, and the whole conditional expression has that type regardless of which branch is taken. `pick ? idx : n` with an `int` and an `unsigned int` therefore has type `unsigned int`: when `pick` is true, `idx = -1` is converted and the value is `4294967295`. `auto m` deduces `unsigned int`, so `m > 100` is true and the program printed `m = 4294967295, m > 100 is true` with both compilers at `-O0` and `-O2`.

The expression reads as "take idx or n", and the mixed signedness is invisible in the source: there is no cast, and the conversion is of a branch that was not even selected on some executions (the type is fixed at compile time). The same mechanism applies to `int` against `double` and `char` against `int` (`decltype` of the conditional is `double` and `int` respectively with both compilers).

Neither compiler warns under `-Wall -Wextra`. With `-Wsign-conversion` both warn at the `?:` line: g++ "conversion to ‘unsigned int’ from ‘int’ may change the sign of the result", clang++ "operand of ? changes signedness: 'int' to 'unsigned int'".

## The fix (`good.cpp`)

Convert both branches to a type that holds both ranges (`long long` here), so the intended value survives. Better, avoid mixing signedness in the first place. Naming the result type (`long long m = ...`) instead of `auto` makes the choice visible.

## Rust (`good.rs`)

Both arms of an `if` expression must have the same type: `if pick { idx } else { n }` with `i32` and `u32` is rejected (`E0308`, "`if` and `else` have incompatible types"). You widen explicitly (`i64::from`).
