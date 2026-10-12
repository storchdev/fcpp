# 064 — Unsequenced side effects

| Case | Mistake |
| --- | --- |
| `01-two-increments` | Two unsequenced modifications of one variable in an arithmetic expression are UB in every standard. |
| `02-index-and-increment` | `a[i] = i++` is UB before C++17 and defined from C++17. |
