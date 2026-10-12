# 039 — Reading uninitialized values

## Why the bad code is wrong (`bad.cpp`)

`int port;` in a function is default-initialization of an automatic object of scalar type: it has an *indeterminate* value. Reading an indeterminate value is undefined behavior (cppreference's default-initialization page; the entry notes C++26 reclassifies reads of such variables as erroneous behavior, which I did not test since no C++26 mode was used here). `parse_port` writes `*out` only on success, and `main` ignores the return value, so with `"not-a-number"` the caller's `port` stays indeterminate and `if (port < 1024)` branches on it.

Because the value is indeterminate, the compiler may assume any value. The sanitizer result depends on whether the read stays in memory: clang++ 23.1.1 with `-fsanitize=memory` reports `WARNING: MemorySanitizer: use-of-uninitialized-value` at `-O0`, `-O1` and `-O2` for `bad.cpp`. `bad.cpp` marks `parse_port` `[[gnu::noinline]]` because without it, in a scratch program, clang++ at `-O1` printed `privileged port` with no MSan report (it had folded the branch away), while `-O0` did report. MSan is a clang tool; AddressSanitizer does not track initialization, which is why the header says `memory`.

Compiler warnings did not catch this form: neither g++ 16.2.1 nor clang++ 23.1.1 emitted a warning under `-Wall -Wextra` on `bad.cpp` (a plain `int limit; if (c) limit = 10; return limit;` does warn, `-Wsometimes-uninitialized` on clang++, but the out-parameter hides the control flow). clang-tidy's analyzer reports `clang-analyzer-core.UndefinedBinaryOperatorResult`: `The left operand of '<' is a garbage value`.

## The fix (`good.cpp`)

Give the variable a value at the declaration (`int port = 8080;`) and check `parse_port`'s result. Better still, return the value (`std::optional<int>`) so there is no out-parameter that can be skipped.

## Rust (`good.rs`)

Rust requires definite initialization on every path; using a possibly-unassigned binding is `E0381` (shown commented). Failure is an `Option`, so there is no out-parameter to forget.
