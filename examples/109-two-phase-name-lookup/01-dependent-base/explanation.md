# 109.01 — Two-phase name lookup: dependent base

## Why the bad code is wrong (`bad.cpp`)

In a template, a name that does not depend on a template parameter is looked up when the template is defined. `hello()` has no dependent arguments, and the base class `Base<T>` is dependent, so it is not searched during that lookup: unqualified lookup finds nothing and the program is ill-formed. Both compilers reject it: g++ "there are no arguments to ‘hello’ that depend on a template parameter, so a declaration of ‘hello’ must be available [-Wtemplate-body]", clang++ "use of undeclared identifier 'hello'".

The surprise is that the member really exists in every instantiation. It is common when moving non-template code into a template. Detection is the compile error (see `compilers.md`).

## The fix (`good.cpp`)

Make the name dependent so lookup is deferred to instantiation: `this->hello()`, `Base<T>::hello()`, or `using Base<T>::hello;` in the derived class. The fixed program prints `hello`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

