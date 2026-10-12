# 060.02 — Integer division corner cases: division by zero

## Why the bad code is wrong (`bad.cpp`)

Integer division by zero is undefined behavior: the standard places no requirement on what happens, and the quotient has no value. On this machine the program was killed by SIGFPE, but that is what the platform did, not what the language promises. Floating-point division by zero is different: in a test with both compilers `1.0 / 0.0` printed `inf` and `-1.0 / 0.0` printed `-inf` with UBSan silent.

The demo hides the zero in a runtime value (`argc - 1`), as real code does: a count or a length that is zero for an empty input. `total / count` is correct for every non-empty input, so tests pass and the crash arrives with the empty case. Both compilers built a program that was killed and dumped core at `-O0` and `-O2`.

Detect it with `-fsanitize=undefined`: both compilers report `runtime error: division by zero` at `-O0`, `-O1` and `-O2`. Both compilers warn when the divisor is a literal zero (g++ `-Wdiv-by-zero`, clang++ `-Wdivision-by-zero`), but not for a runtime zero like this one.

## The fix (`good.cpp`)

Check the divisor before dividing and return something that can express failure (`std::optional`) or choose a documented default for empty input.

## Rust (`good.rs`)

Division by zero panics with "attempt to divide by zero" (also in release builds), and `checked_div` returns `None`; it is never UB.
