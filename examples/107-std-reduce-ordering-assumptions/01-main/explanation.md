# 107 — `std::reduce` ordering assumptions

## Why the bad code is wrong (`bad.cpp`)

`std::reduce` is allowed to apply the operation in any grouping and order, so the operation must be associative and commutative. Subtraction is neither. `std::accumulate` is defined to fold left to right, giving `((100 - 1) - 2) - ...` = 64, while `std::reduce` printed `100` in the same program, with both compilers at `-O0` and `-O2`, with no execution policy at all. In a scratch run with a tracing operation, libstdc++ applied it to the pairs `(1,2)`, `(3,4)`, `(-1,-1)`, `(100,0)` and then the second half the same way: the elements are combined in groups, not left to right.

The answer is a property of this implementation, not of the language: another library, a parallel policy or a different element count may group differently. The program is well-formed and neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it. Floating-point addition shows the same hazard in a milder form because it is not associative either.

## The fix (`good.cpp`)

Use `std::accumulate` when the order matters (it is specified to fold left to right), and `std::reduce` only with an associative and commutative operation (`std::plus`, `std::max`). The fixed program prints `accumulate(minus) = 64, reduce(plus) = 136`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
