# 110.02 — Argument-dependent lookup (ADL): qualified swap

## Why the bad code is wrong (`bad.cpp`)

`std::swap(a, b)` is a qualified call, so ADL does not apply and `lib::swap` is never a candidate; the generic `std::swap` runs. The program counts calls of `lib::swap` and printed `custom swap calls = 0` with both compilers at `-O0` and `-O2`.

The result is correct, which is why it goes unnoticed: only the specialised (possibly cheaper) swap is bypassed. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Use the two-step idiom: `using std::swap; swap(a, b);`, so ADL finds the type's own `swap` and `std::swap` remains the fallback (or `std::ranges::swap` in C++20). The fixed program prints `custom swap calls = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

