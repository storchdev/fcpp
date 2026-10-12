# 029 — `std::span` ownership confusion

A `span` is a pointer and an extent; it never owns or keeps alive its storage.

| Case | Failure mode |
| --- | --- |
| `01-container-reallocation` | The owner is still alive but its buffer moved (`resize`), so the span is stale. Fix: re-create the span after mutating. |
| `02-temporary-container` | The owner was a temporary. `span<const T>` accepts rvalue containers, so this compiles. Fix: name the owner. |
