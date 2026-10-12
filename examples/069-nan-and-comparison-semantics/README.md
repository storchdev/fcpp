# 069 — NaN and comparison semantics

| Case | Mistake |
| --- | --- |
| `01-map-key` | NaN is unordered, so an ordered container treats it as equivalent to an existing key. |
| `02-sort` | `std::sort` with NaN breaks the strict weak ordering requirement, so the result is not sorted. |
