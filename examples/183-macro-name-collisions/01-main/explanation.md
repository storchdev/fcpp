# 183 — Macro name collisions

## Why the bad code is wrong (`bad.cpp`)

Macro replacement happens on preprocessing tokens before C++ name lookup. The function-like macro `max(a, b)` from `legacy_limits.h` sees the token `max` in `std::numeric_limits<int>::max()`. The `std::` qualification does not protect that token. The empty argument list triggers a preprocessing error because the macro requires two arguments.

This is common when a dependency exposes short, generic macro names. The standard-library declaration is valid, so the diagnostic can appear to implicate an innocent call far from the header that introduced the macro. Both compilers reject this case; their exact diagnostics are in `compilers.md`. The header is shared by both versions of this example.

## The fix (`good.cpp`)

Remove the unwanted macro after including the header with `#undef max`. A project that controls the header should avoid exporting a generic macro in the first place. Parenthesizing a specific function name can also prevent a function-like macro invocation, but does not remove the collision for later code.

## Rust (no `good.rs`)

No Rust equivalent is provided for this preprocessor-macro collision.
