# 114 — Template overloads vs. specializations

## Why the bad code is wrong (`bad.cpp`)

Overload resolution chooses among the primary function templates (and plain functions); explicit specializations take no part and are used only afterwards for the template that won. `template <> void f<int*>(int*)` specializes #1 (`f(T)` with `T = int*`). For `f(&x)` both #1 and #2 (`f(T*)`, declared after the specialization) are viable and #2 is more specialized, so #2 wins and #1's specialization is never consulted. The program printed `f(T*)` with both compilers at `-O0` and `-O2`; moving the order of declarations does not change which template wins.

The specialization compiles and looks like the right customization point, which is why this is a trap. Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it.

## The fix (`good.cpp`)

Prefer overloads to function-template specializations, or specialize the template that is actually selected: here `template <> void f<int>(int*)` specializes #2. The fixed program prints `f<int>(int*): specialization of #2`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

