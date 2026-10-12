# 015 — `decltype` vs. `decltype(auto)`

`auto` return types and variables deduce like a by-value template parameter (references and top-level cv dropped). `decltype(auto)` instead applies `decltype` to the initializer or return expression, so it preserves value category — and `decltype` treats an unparenthesized name differently from the same name in parentheses (entry 016). That gives two opposite failure modes.

| Case | Failure |
| --- | --- |
| `01-auto-strips-reference` | `auto` return drops the reference; writes go to a copy. Fix: `decltype(auto)`. |
| `02-parenthesized-return` | `decltype(auto)` + `return (x);` returns a reference to a local. Fix: no parentheses (or plain `auto`). |
