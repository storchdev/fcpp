# 002 — The most vexing parse

## Why the bad code is wrong (`bad.cpp`)

C++ has a disambiguation rule ([stmt.ambig] / [dcl.ambig.res]): anything that *can* be read as a declaration *is* a declaration. `Timer t(Clock());` can be read two ways:

1. a variable `t` of type `Timer`, direct-initialized with a value-initialized temporary `Clock()`; or
2. a function `t` that returns `Timer` and takes one unnamed parameter whose type is "function with no parameters returning `Clock`" (adjusted to `Clock (*)()`).

Reading (2) is a valid declaration, so the standard requires it. The program therefore declares a function and never constructs a `Timer`. Nothing is called, nothing is allocated, and the explicit constructor's `puts` never runs. In `bad.cpp` the only visible effects are that `"Timer constructed"` is missing from the output and that `std::is_function_v<decltype(t)>` is `1`.

The failure often surfaces somewhere else. The line above is accepted, and the first use of `t` (`t.start`, `t.elapsed()`) produces a confusing error such as "request for member 'start' in 't', which is of non-class type 'Timer(Clock (*)())'". If `t` is never used, as with a guard object, the code compiles and silently does nothing. Reviewers miss it because `Timer t(Clock());` looks exactly like the harmless `Timer t(Clock{});`-style code they have read thousands of times.

Detection: g++ warns with `-Wvexing-parse`, which is enabled by default; I observed `warning: parentheses were disambiguated as a function declaration` with g++ 16.2. Clang has the same diagnostic under `-Wvexing-parse`.

## The fix (`good.cpp`)

Use brace initialization, `Timer t{Clock{}};`. Braces cannot begin a parameter declaration, so the line can only be an object. Wrapping the argument in an extra pair of parentheses (`Timer u((Clock()));`) also works, but a tidy-up pass can easily remove them again. Brace initialization has its own traps (see 003 and 004), but those involve classes with `std::initializer_list` constructors. An alternative is `auto t = Timer(Clock());`.

Rust has no analogue: a `let` binding always introduces a value, and function items use the `fn` keyword.
