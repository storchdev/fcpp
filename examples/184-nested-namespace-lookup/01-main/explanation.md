# 184 — Nested namespace lookup can change a call

## Why the bad code is wrong (`bad.cpp`)

Unqualified lookup for `timeout` in `app::test::request_timeout` searches the inner namespace before its enclosing namespace. It finds `app::test::timeout`, so the call returns `0`, even though the caller wanted `app::timeout`, which returns `30`.

The hazard appears during maintenance: adding a same-named helper to an inner namespace can silently change which function an existing unqualified call names. The program remains well formed, and both compilers produced `0` with no warnings under the tested flags. A reviewer must trace the lookup scopes or inspect the runtime result.

## The fix (`good.cpp`)

Qualify the intended function as `app::timeout()`. That makes the dependency on the enclosing namespace explicit and leaves the call unaffected by a new inner declaration.

## Rust (no `good.rs`)

No Rust equivalent is provided for this C++ namespace-lookup case.
