# 066.02 — Operator precedence vs. evaluation order: calls inside one expression

## Why the bad code is wrong (`bad.cpp`)

Precedence says `trace('b', 2) * trace('c', 3)` is grouped first and the product is added to `trace('a', 1)`, so the result is `1 + 2 * 3 = 7`. It does not say that the `*` operands are evaluated before the left operand of `+`. For the built-in `+` and `*` the order in which the operand expressions are evaluated is unspecified, so the grouping is guaranteed and the order of the three calls is not.

The two compilers printed `a b c -> 7` at `-O0` and `-O2`, so here the call to `a` ran first even though its operator binds loosest. That is what these compilers did for this expression, not a guarantee. When the operands are the arguments of a function the order does differ between them: in a test with `sum3(trace('a', 1), trace('b', 2), trace('c', 3))`, g++ printed `c b a` and clang++ printed `a b c` (see case 065).

Neither compiler warns under `-Wall -Wextra`. The failure is when the calls have side effects that depend on each other (logging, a shared counter, reading from a stream) and the code relies on the printed order.

## The fix (`good.cpp`)

Name each result in its own statement, in the order you need, and combine them afterwards.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
