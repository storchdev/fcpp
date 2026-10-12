# 153 — Structured bindings and copying

## Why the bad code is wrong (`bad.cpp`)

`auto [name, n] = e` declares a hidden variable initialized by copying `e`, and the names refer to its members. In the range-`for` the element is copied each iteration, so `++n` modifies the copy and the map is untouched. The program printed `a = 1, b = 2 (expected 2 and 3)` with both compilers at `-O0` and `-O2`.

The code is well-defined and neither compiler warns under `-Wall -Wextra`. Copying large elements also costs time, which is why a plain `auto [..]` in a loop deserves suspicion in review.

## The fix (`good.cpp`)

Bind a reference: `auto& [name, n]` (or `const auto&` for read-only access) so the hidden variable is a reference to the element. The fixed program prints `a = 2, b = 3 (expected 2 and 3)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

