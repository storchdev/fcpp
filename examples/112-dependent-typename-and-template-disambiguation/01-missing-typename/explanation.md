# 112.01 — Dependent `typename` and `template` disambiguation: missing `typename`

## Why the bad code is wrong (`bad.cpp`)

When parsing the template definition the compiler does not know what `C::value_type` is, so a dependent qualified name is assumed to name a value, not a type, unless it is preceded by `typename`. `C::value_type first = ...` therefore does not parse as a declaration. g++ reports "need ‘typename’ before ‘C::value_type’ because ‘C’ is a dependent scope [-Wtemplate-body]" (plus a follow-on "‘first’ was not declared"), clang++ "missing 'typename' prior to dependent type name 'C::value_type'".

The error appears even when every instantiation would have been fine. Detection is the compile error.

## The fix (`good.cpp`)

Write `typename C::value_type first = ...`. The same error occurs with g++ `-std=c++20` for this local variable declaration. The fixed program builds and exits 0.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

