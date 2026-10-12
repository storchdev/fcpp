# 015.02 — `decltype` vs. `decltype(auto)`: a parenthesized return

## Why the bad code is wrong (`bad.cpp`)

For `decltype(auto)`, the return type is `decltype(e)` where `e` is the operand of `return`. An unparenthesized id-expression such as `id` yields the declared type, `int`. But `(id)` is an expression, an lvalue, so `decltype((id))` is `int&` (rule from entry 016). `return (id);` in a `decltype(auto)` function therefore returns `int&` bound to a local that is destroyed on return: undefined behavior when read.

The parentheses are the only difference from correct code. In a scratch test (both compilers) `decltype(auto) f() { static int x; return x; }` returns `int` and `return (x);` returns `int&`.

Observed behavior of `bad.cpp` with `-fsanitize=address`, `ASAN_OPTIONS=detect_stack_use_after_return=1`:

- g++ 16.2.1, `-O0` and `-O1`: `AddressSanitizer: SEGV on unknown address 0x000000000000`. g++ turns the returned dangling reference into a null reference, so ASan reports a read of address 0 rather than a use-after-return.
- clang++ 23.1.1, `-O0`: `AddressSanitizer: stack-use-after-return`. At `-O1` the program printed `42` with no report. That is why the checker uses g++ here.

Both compilers also warn under `-Wall -Wextra`: g++ `warning: reference to local variable ‘id’ returned [-Wreturn-local-addr]`, clang++ `warning: reference to stack memory associated with local variable 'id' returned [-Wreturn-stack-address]`. clang-tidy's `readability-redundant-parentheses` also reports the `return (id);`, as an incidental style finding (the fix it suggests, removing the parentheses, happens to be right). Do not rely on warnings in more complex code where the reference is returned through a helper.

## The fix (`good.cpp`)

Return by value: plain `auto`, or `decltype(auto)` without parentheses. `decltype(auto)` is worth using only where you need to preserve the reference-ness of a forwarded expression (case 01); for ordinary functions use `auto` or an explicit type.

## Rust (`good.rs`)

Returning a reference to a local is a compile error, `E0515` ("cannot return reference to local variable"); `good.rs` shows the rejected form as a comment.
