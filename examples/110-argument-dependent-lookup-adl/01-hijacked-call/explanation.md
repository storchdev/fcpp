# 110.01 — Argument-dependent lookup (ADL): hijacked call

## Why the bad code is wrong (`bad.cpp`)

For an unqualified function call, the candidate set is the ordinary-lookup result plus the functions found in the namespaces associated with the argument types. `w` is a `lib::Widget`, so `lib::show(const Widget&)` joins `::show(int)`, and it is an exact match while `::show(int)` needs the user-defined conversion to `int`. The program printed `lib::show(Widget)` with both compilers at `-O0` and `-O2`.

Nothing is undefined or diagnosed. The call changes meaning when a library adds an overload to its own namespace. Neither compiler warns under `-Wall -Wextra`.

## The fix (`good.cpp`)

Qualify the call (`::show(w)`) when a specific function is intended: a qualified name disables ADL. The fixed program prints `::show(int)`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

