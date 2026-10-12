# 176.01 — Hidden copies in range-based loops: copy per element

## Why the bad code is wrong (`bad.cpp`)

`auto` in `for (auto h : v)` deduces `Heavy`, so each iteration copy-constructs the element. The copy constructor here counts: the program printed `copies during the loop = 1000, sum = 1000` with both compilers at `-O0` and `-O2`. For a type owning heap memory each copy would also allocate.

The code is well-defined and neither compiler warns under `-Wall -Wextra`. It is a one-word difference in review.

## The fix (`good.cpp`)

Bind a reference: `const auto&` for reading (`auto&` to modify). The checker confirms the fixed program builds and runs; it prints `copies during the loop = 0, sum = 1000`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

