# 188 — Accidental switch fallthrough

## Why the bad code is wrong (`bad.cpp`)

A `case` label does not end a C++ `switch` arm. Execution continues into the following statements until a jump such as `break` or `return` changes control flow. For `Charge::base`, the example adds both `10` and `2`, producing `12` instead of `10`.

The missing `break` is a small omission in otherwise valid code. GCC emitted `-Wimplicit-fallthrough` under the tested flags; Clang emitted it when the flag was requested explicitly. These warnings catch this transition, but they do not prove that every possible switch body is correct. Reviewers should check each case's intended exit.

## The fix (`good.cpp`)

End the base case with `break`. When fallthrough is deliberate, C++17's `[[fallthrough]];` states that intent and can suppress the warning.

## Rust (`good.rs`)

Rust `match` arms select one expression; they do not fall through to the next arm. The version here maps each charge directly to its price.
