# 076.01 — Multiple inheritance pointer adjustments: `reinterpret_cast`

## Why the bad code is wrong (`bad.cpp`)

With `struct C : A, B`, the `A` and `B` subobjects live at different offsets inside a `C`; the converting conversions (an implicit conversion, or `static_cast`, between `C*` and `B*`) add or subtract that offset. `reinterpret_cast<B*>(&c)` only reinterprets the address, so it yields a `B*` that points at the `A` subobject. Using it as a `B*` is undefined behavior (it does not point to a `B` object).

In this program `right->b` printed `2` and `wrong->b` printed `1`: the load took the `int` at the start of the `C` object (`A::a`) instead of `B::b`. The offset of `B` in `C` printed as 4 bytes. Both compilers behaved the same way at `-O0` and `-O2`. That the program prints a plausible number instead of crashing is the danger.

Only clang++ diagnoses it: `-Wreinterpret-base-class` ("'reinterpret_cast' from class 'C *' to its base at non-zero offset 'B *' behaves differently from 'static_cast'") under `-Wall -Wextra`; g++ gave no warning. The bug is invisible when the base happens to be the first one (offset 0), so it appears when a second base is added.

## The fix (`good.cpp`)

Use `static_cast` (or the implicit conversion) between base and derived pointers; both apply the adjustment, and `static_cast<C*>(right)` undoes it. The fixed program prints `right->b = 2, back == &c: 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
