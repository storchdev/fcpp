# 106 — `std::accumulate` initial-value type

| Case | Consequence of `T = int` |
| --- | --- |
| `01-double-sum` | Each `double` partial sum is truncated to `int`. |
| `02-int-overflow` | The accumulator is only as wide as `int`, so large sums overflow (undefined behavior). |
