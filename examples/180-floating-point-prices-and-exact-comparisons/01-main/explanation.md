# 180 — Floating-point prices and exact comparisons

## Why the bad code is wrong (`bad.cpp`)

Binary floating point cannot represent `0.10` exactly, so adding ten of them gives `0.99999999999999989` (printed with `%.17g`), `total == 1.00` is false, and `0.1 + 0.2 == 0.3` is false. Both compilers printed the same at `-O0` and `-O2` (this is IEEE 754 `double` behavior on this target, not undefined behavior).

Neither compiler warns under `-Wall -Wextra`. It shows up as one-cent discrepancies, failed equality checks, and order books that sort ties wrongly.

## The fix (`good.cpp`)

Represent money as integers in a minor unit (cents, or a fixed tick size) and format at the edge, or use a decimal type with defined rounding. The fixed program prints `total = 1.00, total == 1.00: 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

