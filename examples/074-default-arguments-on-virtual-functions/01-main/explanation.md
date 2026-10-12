# 074 — Default arguments on virtual functions

## Why the bad code is wrong (`bad.cpp`)

A virtual function call selects the function body by the dynamic type of the object, but default arguments are substituted at compile time from the declaration found through the static type of the expression. `b.greet()` has static type `Base`, so the default `1` from `Base::greet` is supplied, and then the call is dispatched to `Derived::greet`: the body of the derived class runs with the base class's default. `d.greet()` has static type `Derived` and gets `5`. Both compilers printed `Derived::greet(1)` then `Derived::greet(5)` at `-O0` and `-O2`.

Overriding functions are allowed to declare different defaults, so nothing is diagnosed by either compiler under `-Wall -Wextra`. The defaults are easy to change in one class and forget in the other, and the bug depends on the type of the variable that happens to be used at the call site.

`clang-tidy -checks=google-default-arguments` reports both declarations ("default arguments on virtual or override methods are prohibited").

## The fix (`good.cpp`)

Do not put default arguments on virtual functions. Use the non-virtual interface idiom: a public non-virtual `greet(int times = 1)` that forwards to a private virtual `do_greet(int times)`, so the default exists in one place and the override has none. Overloads (`greet()` calling `greet(1)`) work too.

## Rust (`good.rs`)

Rust has no default arguments. A trait method that wants a default is written once in the trait (`fn greet(&self) { self.greet_n(1) }`), and the demo prints `Derived::greet(1)` for both the `dyn Greeter` call and the direct call.
