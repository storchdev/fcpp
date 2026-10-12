# 062 — Truncation and overflow during numeric casts

| Case | Mistake |
| --- | --- |
| `01-float-to-int` | A floating value outside the destination integer's range is UB to convert. |
| `02-narrowing-integer` | Integer narrowing and sign changes never trap; they silently change the value. |
