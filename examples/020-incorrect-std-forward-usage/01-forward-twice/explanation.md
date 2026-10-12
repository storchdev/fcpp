# 020.01 — Incorrect `std::forward` usage: forwarding twice

## Why the bad code is wrong (`bad.cpp`)

For an rvalue argument, `T` deduces as `std::string` and `std::forward<T>(item)` is `static_cast<std::string&&>(item)`: an xvalue, exactly like `std::move`. `store(std::forward<T>(item))` initializes `store`'s by-value parameter by move construction, which empties `item`. The second `audit(std::forward<T>(item))` forwards a moved-from string. Output on g++ 16.2.1 and clang++ 23.1.1 (libstdc++): `store: "a-long-enough-string-to-defeat-sso-0123456789"` then `audit: ""`. For an lvalue argument both calls copy and the code works, so it passes tests that use named variables.

The behavior is defined (a moved-from `std::string` is valid but unspecified), which is why there is no sanitizer report and no `-Wall -Wextra` warning. Detection: clang-tidy `bugprone-use-after-move` reports `'item' used after it was forwarded` (verified). A longer string is used in the example so that the move is observable rather than hidden by the small-string optimization.

## The fix (`good.cpp`)

Forward only on the last use of the name. Earlier uses treat the object as an lvalue (`store(item)` with a `const&` parameter). In general, `std::forward` and `std::move` are "consume" operations and should appear at most once per path.
