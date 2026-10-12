# 043 — Pointer arithmetic outside an array

Pointer arithmetic is defined only while the result stays within one array object (or one past its end). Being inside the same enclosing object or the same allocation is not enough.

| Case | Mistake |
| --- | --- |
| `01-index-past-member-array` | Indexing a member array past its end into the next member of the same struct. |
| `02-bounds-check-by-forming-pointer` | Checking a bound by computing `buf + n`, which is itself UB when `n` is out of range. |
