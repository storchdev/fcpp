# 135.02 — Incorrect compare-exchange loops: `expected` is overwritten

## Why the bad code is wrong (`bad.cpp`)

Both `compare_exchange_weak` and `compare_exchange_strong` take `expected` by reference and, when the comparison fails, load the atomic's current value into it. After the failed exchange here, `expected` is `5`, not `0`: the program printed `lost the race; state was 0, but expected now reads 5` with both compilers at `-O0` and `-O2` (the "state was 0" text is what the code assumes).

The code is well-defined. It misreports because the argument was treated as an input only. Neither compiler warns under `-Wall -Wextra`. (`compare_exchange_weak` may also fail spuriously, which is why it is normally used in a loop; I could not provoke a spurious failure here.)

## The fix (`good.cpp`)

Copy the value you want to remember (`const int wanted = expected;`) before the call, or treat `expected` after failure as "the value that was found". The fixed program prints `lost the race; wanted 0, found 5`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

