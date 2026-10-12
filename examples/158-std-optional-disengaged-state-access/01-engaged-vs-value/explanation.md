# 158.01 — `std::optional` disengaged-state access: engaged vs. value

## Why the bad code is wrong (`bad.cpp`)

`optional<T>`'s `explicit operator bool` is `has_value()`. For `optional<bool>` holding `false`, `if (flag)` is therefore true. The program printed `flag is set` for a flag that holds `false`, with both compilers at `-O0` and `-O2`.

The code is well-defined and neither compiler warns under `-Wall -Wextra`; the same applies to `optional<int>` holding 0.

## The fix (`good.cpp`)

Say which test you mean: `flag.has_value()` for presence, `*flag` / `flag.value()` for the value after checking presence, or `flag.value_or(false)` as in `good.cpp`. The fixed program prints `flag is not set`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

