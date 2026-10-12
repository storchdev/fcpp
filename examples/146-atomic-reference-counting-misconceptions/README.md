# 146 — Atomic reference-counting misconceptions

| Case | Misconception |
| --- | --- |
| `01-shared-object` | An atomic count means the pointee is thread-safe. |
| `02-shared-pointer-object` | A `shared_ptr` object can be copied or assigned concurrently from several threads. |

