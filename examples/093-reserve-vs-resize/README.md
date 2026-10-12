# 093 — `reserve()` vs. `resize()`

| Case | Mistake |
| --- | --- |
| `01-reserve-then-index` | `reserve` allocates capacity but creates no elements; indexing them is undefined. |
| `02-resize-then-push-back` | `resize` creates elements; `push_back` afterwards appends behind them. |
