# 096 — Past-the-end iterator invalidation

| Case | Operation that invalidates `end()` |
| --- | --- |
| `01-push-back` | Reallocation by `push_back`: the cached `end` points into freed storage. |
| `02-erase` | `erase`: `end()` moves, the cached copy still points one element too far. |
