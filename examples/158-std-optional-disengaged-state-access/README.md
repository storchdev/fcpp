# 158 — `std::optional` disengaged-state access

| Case | Mistake |
| --- | --- |
| `01-engaged-vs-value` | `if (opt)` tests presence, not the truthiness of the contained value. |
| `02-unchecked-deref` | `*opt` on an empty optional is undefined behavior, unlike `value()`. |

