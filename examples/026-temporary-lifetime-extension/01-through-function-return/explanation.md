# 026.01 — Temporary lifetime extension: through a function return

## Why the bad code is wrong (`bad.cpp`)

When a reference is initialized directly from a prvalue, the temporary is materialized and its lifetime is extended to that of the reference. `const std::string& direct = std::string("…");` therefore stays valid for the whole block. The rule is syntactic: the reference must be bound *to the temporary itself*. cppreference's reference-initialization page lists the exception: when a temporary is bound to a function's reference parameter, it persists only until the end of the full-expression containing the call, and if the function returns a reference that outlives the full-expression, it is a dangling reference.

`pick` returns its argument by reference. In `via_call = pick(std::string("…"))` the temporary is bound to `pick`'s parameter, not to `via_call`; `via_call` is bound to whatever `pick` returned, and nothing extends the temporary. It dies at the `;`. Reading it afterwards is undefined behavior. g++ 16.2.1 and clang++ 23.1.1 with `-fsanitize=address` both report `stack-use-after-scope` at the `c_str()` read (`-std=c++17`, `-O1`); the first line (`direct`) prints fine, which is why code like this can appear to work in tests.

Detection: g++ warns under `-Wall -Wextra`: `warning: possibly dangling reference to a temporary [-Wdangling-reference]` (clang++ 23.1.1 does not warn here). clang-tidy `bugprone-return-const-ref-from-parameter` reports `returning a constant reference parameter may cause use-after-free when the parameter is constructed from a temporary` on `pick` itself, which is the earlier and more reliable catch.

## The fix (`good.cpp`)

Return by value. `pick` then yields a prvalue, which `via_call` binds directly, so the result is extended. If the function must return a reference, the caller has to keep the argument alive in a named variable.

## Rust (`good.rs`)

Rust has the same two tiers: `let direct = &String::from("…");` extends the temporary, while `let via_call = pick(&String::from("…")); println!("{}", via_call);` is rejected with `error[E0716]: temporary value dropped while borrowed` (verified with rustc 1.99.0; shown commented in `good.rs`). The signature `fn pick(s: &String) -> &String` ties the result to the argument, so the compiler sees the dangling use.
