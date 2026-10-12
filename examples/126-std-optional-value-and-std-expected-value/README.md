# 126 — `std::optional::value()` and `std::expected::value()`

| Case | Accessor behavior |
| --- | --- |
| `01-deref-empty` | `operator*` on an empty `optional` is undefined; only `value()` checks. |
| `02-expected-value-throws` | `expected::value()` throws `bad_expected_access` when it holds an error. |

