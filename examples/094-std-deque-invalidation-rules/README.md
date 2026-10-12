# 094 — `std::deque` invalidation rules

| Case | Rule |
| --- | --- |
| `01-reference-across-middle-insert` | A middle `insert` invalidates all iterators and references. |
| `02-iterator-across-push-back` | `push_back` invalidates iterators but leaves references to existing elements valid. |
