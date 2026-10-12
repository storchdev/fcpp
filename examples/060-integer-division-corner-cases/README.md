# 060 — Integer division corner cases

| Case | Mistake |
| --- | --- |
| `01-int-min-by-minus-one` | `INT_MIN / -1` is not representable, so it is UB. |
| `02-divide-by-zero` | Integer division by a runtime zero is UB. |
