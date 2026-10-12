# 176 — Hidden copies in range-based loops

| Case | Surprise |
| --- | --- |
| `01-copy-per-element` | `for (auto x : v)` deduces a value type and copies every element. |
| `02-vector-bool-proxy` | `std::vector<bool>` iterates by proxy value, so `auto&` does not compile. |

