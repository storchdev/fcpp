# 056 — Signed integer overflow

## Why the bad code is wrong (`bad.cpp`)

For signed integer types, the C++ standard says the result of an arithmetic operation that is not representable is **undefined behavior** (unsigned types, by contrast, wrap modulo 2^N). That is not a statement about what the hardware does — it is a license for the optimizer: it may assume a program never executes a signed overflow.

`will_overflow(x)` returns `x + 1 < x`. If signed overflow never happens, `x + 1` is always greater than `x`, so the compiler is allowed to fold the whole function to `return false`. With GCC the answer is `0` at every optimization level, because GCC folds the expression even at `-O0`; clang prints `1` at `-O0` (the hardware wrap really happens) and `0` at `-O2`; `-fwrapv` makes both print `1`. The same source gives different answers depending on compiler and flags, and none of them is "wrong" as far as the standard is concerned.

`count_up` is the loop version: the author wants the loop to end when `i` wraps around below `start`. Since `i >= start` is always true if `++i` never overflows, the compiler can treat the condition as always true and the loop becomes infinite (bounded here only by the `break`), or can transform it based on the same assumption. Real-world consequences include security checks (`if (len + n < len)`) silently removed by the compiler, and index arithmetic that is "optimized" using the no-overflow assumption (e.g. widening a 32-bit `int` loop counter to 64 bits).

Detect it with `-fsanitize=undefined` (UBSan reports `signed integer overflow`), or `-ftrapv`. `-fwrapv` makes GCC/Clang define it as wraparound, but that is a non-portable dialect.

## The fix (`good.cpp`)

Check *before* the operation using conditions that cannot themselves overflow (`x == INT_MAX`, or `a > INT_MAX - b`), use the checked builtins (`__builtin_add_overflow`; C++26 adds `std::add_sat` and friends in `<numeric>`), or do the arithmetic in an unsigned type when you explicitly want modular behavior. Prefer a wider type when the range requires it.

## Rust (`good.rs`)

Overflow is never UB in Rust. Plain `+` panics in debug builds and wraps in release; for anything intentional you pick `checked_*`, `wrapping_*`, `saturating_*` or `overflowing_*`.
