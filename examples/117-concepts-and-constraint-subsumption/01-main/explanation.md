# 117 — Concepts and constraint subsumption

## Why the bad code is wrong (`bad.cpp`)

Constraints are normalized into atomic constraints, and one declaration subsumes another only if its atomic constraints are the same expressions from the same source location, not merely equivalent ones. The two `std::is_integral_v<T>` uses are written separately, so they are different atomic constraints, and neither overload is more constrained: `f(1)` is ambiguous. g++ "call of overloaded ‘f(int)’ is ambiguous", clang++ "call to 'f' is ambiguous".

The same logic written with concepts (`std::integral<T>`) is accepted because both overloads name the same concept. Detection is the compile error.

## The fix (`good.cpp`)

Constrain with named concepts so the common part is the same atomic constraint (`std::integral<T>` and `std::signed_integral<T>`). The fixed program prints `signed integral`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

