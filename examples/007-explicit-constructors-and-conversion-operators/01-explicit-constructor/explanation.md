# 007.01 — `explicit` constructors: `return {...}` and copy-initialization

## Why the bad code is wrong (`bad.cpp`)

An `explicit` constructor ([class.conv.ctor], [dcl.init.list]) is considered only for direct-initialization. It is not a candidate for copy-initialization (`Point p = x;`, passing an argument, `return x;`) and, for list forms, it makes copy-list-initialization ill-formed *after* it is selected. So `return {0, 0};`, `Point p = {1, 2};` and passing `{1, 2}` to a `Point` parameter all fail when `Point(int, int)` is `explicit`. g++ 16.2 reports `error: converting to 'Point' from initializer list would use explicit constructor 'Point::Point(int, int)'`.

Two things catch people out:

- Since C++11, `explicit` is meaningful on constructors with any number of parameters, not just one-argument ones.
- The failure shows up when someone adds `explicit` (or a linter pass adds it everywhere): every `return {a, b};` and every `f({a, b})` call site stops compiling. Note also that the rule is "selected, then rejected": in copy-list-initialization the explicit constructor still takes part in overload resolution, and if it is the best match the program is ill-formed even though a non-explicit constructor exists. I checked this with `S s = {1, 2L};` where `S(int, int)` is non-explicit and `explicit S(int, long)` is the better match; both g++ and clang++ reject it.

## The fix (`good.cpp`)

Name the type (`return Point{0, 0};`) or use direct-initialization (`Point q(1, 2);`, `Point r{3, 4};`), which accepts explicit constructors. Keep `explicit` on constructors that do not describe a natural, lossless conversion; that is the point of the keyword.

Rust has no implicit conversion for user types, so there is no equivalent of the keyword: a struct literal or an explicit `From::from` call is always required.
