# 064.02 — Unsequenced side effects: `a[i] = i++` before C++17

## Why the bad code is wrong (`bad.cpp`)

Before C++17 the two operands of `=` were unsequenced, so `a[i] = i++` reads `i` (to choose the element) while another side effect modifies `i`: undefined behavior. C++17 sequences the right operand of an assignment before the left operand, which makes `a[i] = i++ + 10` well-defined (the right side runs first, so `i` is incremented and the store goes to `a[1]`). The file is compiled with `-std=c++14` to show the old rule, and the same source is well-defined when compiled as C++17.

Both compilers printed `a[0]=0 a[1]=10 i=1` at `-O0` and `-O2` under `-std=c++14` and under `-std=c++17`. The identical output hides the difference between UB and defined behavior; do not read it as a promise.

Warnings differ. Under `-std=c++14`: g++ reports `-Wsequence-point` ("operation on ‘i’ may be undefined", twice) and clang++ reports `-Wunsequenced` ("unsequenced modification and access to 'i'"). Under `-std=c++17` g++ still reports one `-Wsequence-point` for this line, although the code is defined there, while clang++ reports nothing.

## The fix (`good.cpp`)

Put the increment in its own statement so the order is explicit in every standard, or require C++17 (or later) and know that the rule depends on it. Prefer the explicit statements: readers and older compilers do not know the sequencing rule.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
