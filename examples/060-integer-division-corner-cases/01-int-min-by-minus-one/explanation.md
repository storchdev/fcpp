# 060.01 — Integer division corner cases: `INT_MIN / -1`

## Why the bad code is wrong (`bad.cpp`)

For `/` and `%` on integers, if the quotient `a/b` is not representable in the result type the behavior of both operations is undefined. Besides a zero divisor (case 02), the only signed input that triggers this is `INT_MIN / -1` (more generally, the minimum value of the type divided by `-1`): the mathematically correct answer is `2147483648`, one more than `INT_MAX`. `INT_MIN % -1` is undefined for the same reason, even though its mathematical result is `0`: both compilers' UBSan reported it (`division of -2147483648 by -1 cannot be represented in type 'int'`).

Both compilers produced a program that was killed and dumped core at `-O0` and `-O2`, and under UBSan the process dies of SIGFPE (g++ exit status 136) rather than printing a wrapped value; that is what this x86-64 machine did, not something the language promises. Nothing about the source looks suspicious: `a / b` is correct for every pair except one, and the pair is rare, which is how it turns into a denial-of-service on input like "divide by -1".

Detect it with `-fsanitize=undefined`: both compilers report `division of -2147483648 by -1 cannot be represented in type 'int'` at `-O0`, `-O1` and `-O2`. Neither compiler warns here because the divisor is not a constant in the demo (`compilers.md`).

## The fix (`good.cpp`)

Reject the two failing inputs before dividing (`b == 0` and `a == INT_MIN && b == -1`) and return a value that represents failure (`std::optional`), or widen to `long long` before dividing if the result must be defined for all `int` inputs. Using unsigned types avoids this case but not division by zero.

## Rust (`good.rs`)

Rust never treats this as UB: `a / b` panics with "attempt to divide with overflow" (also in release builds with `-O`), `checked_div` returns `None`, and `wrapping_div` returns `i32::MIN` if wraparound is what you want.
