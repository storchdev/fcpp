# 061 — Bit shifts and signed integers

| Case | Mistake |
| --- | --- |
| `01-shift-count` | Shifting by a count at or beyond the operand's width (or a negative count) is UB. |
| `02-negative-left-shift` | Left-shifting a negative value is UB before C++20 and defined from C++20. |
