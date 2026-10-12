# 053 — Mismatched allocation and deallocation

Every allocation function has exactly one matching deallocation: `new`/`delete`, `new[]`/`delete[]`, `malloc`/`free`.

| Case | Mismatch |
| --- | --- |
| `01-array-vs-scalar` | `new[]` released with `delete`. |
| `02-malloc-vs-delete` | `malloc` released with `delete`. |
