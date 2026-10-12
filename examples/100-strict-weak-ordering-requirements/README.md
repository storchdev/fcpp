# 100 — Strict weak ordering requirements

| Case | Algorithm / container | Symptom |
| --- | --- | --- |
| `01-sort-less-equal` | `std::sort` | `<=` as comparator: the unguarded insertion loop runs past the range (heap buffer overflow). |
| `02-map-less-equal` | `std::map` | `std::less_equal` as the key comparator: equal keys are neither deduplicated nor found. |
