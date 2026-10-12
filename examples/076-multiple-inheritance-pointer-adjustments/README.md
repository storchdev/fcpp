# 076 — Multiple inheritance pointer adjustments

| Case | Mistake |
| --- | --- |
| `01-reinterpret-cast` | `reinterpret_cast` from `C*` to its second base `B*` keeps the address of the first base. |
| `02-void-pointer` | A `C*` stored as `void*` is read back as `B*`, which is not the same address. |
