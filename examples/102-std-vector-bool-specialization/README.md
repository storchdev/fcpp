# 102 — `std::vector<bool>` specialization

| Case | Consequence of the bit-packed proxy |
| --- | --- |
| `01-auto-proxy` | `auto x = v[i]` deduces the proxy, not `bool`, so `x` aliases the element. |
| `02-reference-binding` | There is no `bool&`: `for (auto& b : v)` does not compile. |
| `03-adjacent-race` | Distinct elements share bytes, so two threads writing different elements race. |
