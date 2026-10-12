# 067 — Conditional operator type deduction

| Case | Mistake |
| --- | --- |
| `01-common-type` | Differently typed branches are converted to a common type, which can change sign or value. |
| `02-copy-not-alias` | With differently typed branches the result is a copy, not an alias of the chosen object. |
