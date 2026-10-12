# 027.01 — Reference members bound to temporaries: constructor parameter

## Why the bad code is wrong (`bad.cpp`)

`Logger logger("…");` converts the string literal to a temporary `std::string` to initialize the constructor's `const std::string&` parameter. That temporary is bound to a function parameter, so it lives until the end of the full-expression containing the call, i.e. the semicolon after `Logger logger("…")`. The mem-initializer `prefix_(prefix)` then binds the member to the *parameter's referent*, and nothing extends the temporary beyond the constructor call. `logger.log(…)` reads a destroyed string: undefined behavior, reported by AddressSanitizer as `stack-use-after-scope` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`).

A reference member bound *directly* to a temporary in the mem-initializer is a different, and diagnosed, case. In a scratch program `L() : r(std::string("tmp")) {}` gave g++ `warning: a temporary bound to ‘L::r’ only persists until the constructor exits [-Wextra]` and clang++ `error: reference member 'r' binds to a temporary object whose lifetime would be shorter than the lifetime of the constructed object`. cppreference notes this is ill-formed since CWG 1696. Passing through a parameter, as in `bad.cpp`, hides it: no `-Wall -Wextra` warning from either compiler, and no clang-tidy check I ran reported it. The implicit `const char*` → `std::string` conversion makes the temporary invisible at the call site.

## The fix (`good.cpp`)

Store a value: `std::string prefix_;` initialized by `std::move(prefix)` from a by-value parameter. If a reference member is intended, make the lifetime contract visible (take `const std::string&` only for callers that hold a named object, and delete the rvalue overload: `Logger(std::string&&) = delete;`).

## Rust (`good.rs`)

A struct holding a reference has an explicit lifetime parameter (`Logger<'a>`), and the borrow checker ties it to the referent. Passing a temporary and then using the logger is `E0716`, shown commented in `good.rs`.
