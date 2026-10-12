# 056 — Signed integer overflow

## Why the bad code is wrong (`bad.cpp`)

For signed integer types, the C++ standard says the result of an arithmetic operation that is not representable is **undefined behavior** (unsigned types, by contrast, wrap modulo 2^N). That is not a statement about what the hardware does — it is a license for the optimizer: it may assume a program never executes a signed overflow.

`will_overflow(x)` returns `x + 1 < x`. If signed overflow never happens, `x + 1` is always greater than `x`, so the compiler is allowed to fold the whole function to `return false`. With g++ the answer is `0` at `-O0`, `-O1` and `-O2`; clang++ prints `1` at `-O0` and `0` at `-O1` and `-O2`; `-fwrapv` makes both print `1` (`compilers.md`). The same source gives different answers depending on compiler and flags, and none of them is "wrong" as far as the standard is concerned.

`count_up` is the loop version: the author wants the loop to end when `i` wraps around below `start`. Since `i >= start` is always true if `++i` never overflows, the compiler can treat the condition as always true and the compiler may treat the loop as one that never ends on its own (here only the `break` stops it), or may transform it based on the same assumption. What actually happened is in `compilers.md`. Real-world consequences include security checks (`if (len + n < len)`) silently removed by the compiler, and index arithmetic that is "optimized" using the no-overflow assumption (e.g. widening a 32-bit `int` loop counter to 64 bits).

Detect it with `-fsanitize=undefined`: both compilers report `runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'` for both the `x + 1` at line 8 and the `++i` at line 13, at `-O0`, `-O1` and `-O2`. `-ftrapv` is much less reliable (see `compilers.md`). `-fwrapv` makes both compilers define the overflow as wraparound, but that is a non-portable dialect.

## The fix (`good.cpp`)

Check *before* the operation using conditions that cannot themselves overflow (`x == INT_MAX`, or `a > INT_MAX - b`), use the checked builtins (`__builtin_add_overflow`; C++26 adds `std::add_sat` and friends in `<numeric>`), or do the arithmetic in an unsigned type when you explicitly want modular behavior. Prefer a wider type when the range requires it.

## Rust (`good.rs`)

Overflow is never UB in Rust. Plain `+` panics in debug builds and wraps in release; for anything intentional you pick `checked_*`, `wrapping_*`, `saturating_*` or `overflowing_*`.
