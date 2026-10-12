# 092 — `std::vector` reallocation invalidation

| Case | Failure mode |
| --- | --- |
| `01-dangling-reference` | `push_back` beyond capacity reallocates and frees the old storage: pointers, references and iterators dangle (use after free). |
| `02-insert-shifts` | `insert` without reallocation still shifts the elements: an old iterator designates a different element. |
