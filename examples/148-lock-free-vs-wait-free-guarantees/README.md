# 148 — Lock-free vs. wait-free guarantees

| Case | Point |
| --- | --- |
| `01-non-lock-free-atomic` | `std::atomic<T>` compiles for large `T` but is not lock-free. |
| `02-cas-retries` | A lock-free CAS loop lets individual threads retry without a bound. |

