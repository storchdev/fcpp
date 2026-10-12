# 066 — Operator precedence vs. evaluation order

| Case | Mistake |
| --- | --- |
| `01-bitand-equality` | `flags & MASK == 0` groups as `flags & (MASK == 0)`: a grouping bug. |
| `02-calls-in-expression` | Precedence fixes the grouping of `a() + b() * c()` but not the order in which the calls run. |
