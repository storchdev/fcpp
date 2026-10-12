# 118 — `if constexpr` discarded branches

## Why the bad code is wrong (`bad.cpp`)

A discarded statement of `if constexpr` is only exempt from instantiation inside a template, and only for constructs that depend on a template parameter. Outside a template, or for non-dependent code, the statement is still parsed and name-looked-up, so `undeclared_function()` is an error even though the branch is never executed. g++ "‘undeclared_function’ was not declared in this scope", clang++ "use of undeclared identifier 'undeclared_function'".

In a scratch template test, an undeclared non-dependent name in a discarded branch was also an error on both compilers (g++ "there are no arguments to ‘undeclared_nondep’ that depend on a template parameter...", clang++ "use of undeclared identifier"), while a dependent member call (`v.nothing()`) in a discarded branch was accepted. Detection is the compile error.

## The fix (`good.cpp`)

Make the discarded code depend on the template parameter, as in the good program (`v.print()` with `T` an `int` is not instantiated). The fixed program prints `int 5`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

