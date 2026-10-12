# 052 — Object layout and `offsetof` assumptions

## Why the bad code is wrong (`bad.cpp`)

`offsetof` is required to work for standard-layout types; for other classes it is only conditionally supported, so the result is implementation-specific. `bad.cpp` uses three common ways of losing standard layout, each proven with `static_assert(!std::is_standard_layout_v<…>)` on both compilers:

- `Derived` has non-static data members in both `Derived` and its base `Base`.
- `Poly` has a virtual function (the object also carries a hidden vptr).
- `Mixed` has non-static data members with different access control (`public` and `private`).

Both compilers accept the code and print plausible numbers (`4` for `offsetof(Derived, b)` and `8` for `offsetof(Poly, x)`), which is what makes the assumption feel safe; nothing in the language says another compiler, ABI or later class change keeps them. They also diagnose it under `-Wall -Wextra`: g++ 16.2.1 `warning: ‘offsetof’ within non-standard-layout type ‘Derived’ is conditionally-supported [-Winvalid-offsetof]` and the same for `Poly`; clang++ 23.1.1 `warning: 'offsetof' on non-standard-layout type 'Derived' [-Winvalid-offsetof]` (clang++ also emitted an unrelated `-Wunused-private-field` for `Mixed`).

## The fix (`good.cpp`)

Use `offsetof` only on standard-layout types, and guard the assumption with `static_assert(std::is_standard_layout_v<Header>)` so a later change breaks the build instead of silently shifting layout. For other types, avoid layout assumptions altogether (pointer-to-member, explicit serialization).

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
