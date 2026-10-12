# 063 — Character signedness

| Case | Mistake |
| --- | --- |
| `01-widening` | Plain `char` widens to a negative `int` where it is signed, so comparisons with byte values fail. |
| `02-table-index` | A negative `char` used as an array index reads before the array. |
