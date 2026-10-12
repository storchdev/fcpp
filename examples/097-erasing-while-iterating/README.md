# 097 — Erasing while iterating

| Case | Failure mode |
| --- | --- |
| `01-unordered-map` | `erase(it)` frees the node, then `++it` advances it: use after free. |
| `02-vector` | `erase(it)` shifts the tail, then `++it` skips the element that moved into its place. |
