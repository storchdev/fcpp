# 075.01 — Name hiding in inheritance: hidden overloads

## Why the bad code is wrong (`bad.cpp`)

Name lookup finds the name in the innermost scope that declares it and stops there, before overload resolution. `Derived::set(double)` declares the name `set` in `Derived`, so lookup of `d.set` never reaches `Base`, and both `Base::set` overloads are hidden even though their parameter lists differ. Overload resolution then sees only `set(double)`, and `d.set("x")` has no conversion from `const char*` to `double`.

The program is ill-formed and both compilers reject it, with different text: g++ "cannot convert ‘const char [2]’ to ‘double’", clang++ "cannot initialize a parameter of type 'double' with an lvalue of type 'const char[2]'". Neither message mentions that `Base::set` exists, which is why the error is confusing.

## The fix (`good.cpp`)

Add a using-declaration `using Base::set;` in `Derived`, which brings the base overloads into the derived scope so that overload resolution considers all of them. (Or call the base function explicitly, `d.Base::set("x")`.)

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
