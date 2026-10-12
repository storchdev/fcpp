# 135 — Incorrect compare-exchange loops

| Case | Mistake |
| --- | --- |
| `01-stale-desired` | `expected` is refreshed on failure, but the new value computed before the loop is not. |
| `02-expected-overwritten` | Code assumes `expected` still holds what it was set to after a failed exchange. |

