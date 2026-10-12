# 019 — Forwarding references vs. rvalue references

`T&&` is a forwarding reference only when `T` is a template parameter of *the function being called* and the parameter is exactly `T&&` (no `const`, not wrapped in another template). It binds lvalues and rvalues and deduces `T` as `X&` or `X`. Anything else spelled with `&&` is a plain rvalue reference.

| Case | Mix-up |
| --- | --- |
| `01-move-on-forwarding-ref` | Treating a forwarding reference as an rvalue reference: `std::move(line)` steals from lvalue callers. |
| `02-not-a-forwarding-ref` | Treating an rvalue reference as a forwarding reference: `std::vector<T>&&` rejects lvalues. |
