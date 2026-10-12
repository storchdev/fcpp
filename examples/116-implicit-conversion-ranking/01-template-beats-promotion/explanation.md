# 116.01 — Implicit conversion ranking: template beats promotion

## Why the bad code is wrong (`bad.cpp`)

Overload resolution compares conversion sequences first and only prefers a non-template over a template when the sequences are equal. For `g('a')`, `g(int)` needs the integral promotion `char -> int`, while `g<char>(char)` is an exact match, which ranks better, so the template is chosen. The program printed `g(T)` with both compilers at `-O0` and `-O2`.

People expect the non-template to win "because it is non-template". Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it.

## The fix (`good.cpp`)

Make the argument match the non-template exactly (`g(static_cast<int>('a'))`), or constrain or remove the template. The fixed program prints `g(int)` then `g(T)` (`g<>(1)` explicitly selects the template).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

