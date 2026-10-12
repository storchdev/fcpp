# 099 — `insert`, `emplace`, and `try_emplace` semantics

| Case | Mistake |
| --- | --- |
| `01-insert-keeps-old` | `insert` does not overwrite an existing key; the returned `bool` says so. |
| `02-insert-consumes-argument` | `insert({key, std::move(x)})` moves `x` into a temporary pair before the key is looked up, so `x` is lost even when nothing is inserted. |
