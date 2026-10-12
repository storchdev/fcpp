# 068 — Floating-point non-associativity

## Why the bad code is wrong (`bad.cpp`)

Every floating-point addition rounds its exact result to the nearest representable value, so `(a + b) + c` and `a + (b + c)` can round differently; addition is commutative but not associative. With `a = 1e16`, `b = -1e16` and `c = 1.0`: `(a + b) + c` is `0 + 1 = 1`, but `b + c` is `-1e16 + 1`, which rounds back to `-1e16` (a `double` near `1e16` has a spacing of 2), so `a + (b + c)` is `0`. The program printed `1` and `0` with both compilers at `-O0` and `-O2`.

That is not UB or a compiler bug; each result is the correctly rounded value of the grouping you wrote. It becomes a footgun in three ways. A sum over a container depends on the order of its elements. A refactor that regroups an expression changes the answer. And the compilers can regroup for you: with `-O2 -ffast-math` both compilers printed `(a + b) + c = 1` and `a + (b + c) = 1` for this program, i.e. the optimizer was allowed to reassociate and did (the exact transformation was not investigated). `-O2` alone changed nothing, and neither did `-ffp-contract=off` or `-march=native`.

Reviewers see two mathematically equal expressions; no warning exists for it. Neither compiler warns under `-Wall -Wextra`, and no sanitizer applies.

## The fix (`good.cpp`)

There is no regrouping that is right for all inputs. Decide what matters: for exact results use integers or fixed-point (money in cents), and for floating-point compare with a tolerance scaled to the operands (`nearly_equal(left, right, scale)` in the demo, which accepts the `1` versus `0` at the scale `1e16`) instead of `==`. Do not rely on summation order, and avoid `-ffast-math` where results must be reproducible. Compensated summation (Kahan) helps in some cases but is not a cure: for the input order `{1, big, -big}` my Kahan implementation still produced `0`.

## Rust (`good.rs`)

Rust's floating-point arithmetic has the same rounding, and the demo prints the same `1` and `0`: the compiler uses the grouping you wrote.
