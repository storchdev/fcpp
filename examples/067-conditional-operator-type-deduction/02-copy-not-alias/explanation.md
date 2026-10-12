# 067.02 — Conditional operator type deduction: a copy, not an alias

## Why the bad code is wrong (`bad.cpp`)

If the second and third operands are lvalues of the same type, the result is an lvalue designating the chosen operand, so `(c ? a : b) = 1` assigns to `a` or `b`. If their types differ, one operand is converted to the other's type where an implicit conversion exists, and the result is a prvalue. Here `s` is a `std::string` and `"fallback"` is a `const char[9]`; the literal converts to `std::string`, so the conditional is a prvalue `std::string` and `s` itself is **copied**.

The const reference then binds to that temporary, and the temporary's lifetime is extended to the reference's. The result is that `r` is not an alias of `s`: after `s = "changed"` the program printed `r = original, s = changed` with both compilers at `-O0` and `-O2`. The same happens when the copy is expensive (a large string or container copied on every evaluation) and when the code expected a mutable reference to the chosen object.

Neither compiler warns under `-Wall -Wextra`, and no sanitizer applies.

## The fix (`good.cpp`)

Give both operands the same type (here a `std::string fallback`), so the conditional is an lvalue and `r` really refers to `s` (the demo prints `r = changed, s = changed`).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
