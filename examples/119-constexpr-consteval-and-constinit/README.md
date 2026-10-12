# 119 — `constexpr`, `consteval`, and `constinit`

| Case | Keyword | Trap |
| --- | --- | --- |
| `01-consteval-runtime-arg` | `consteval` | Every call must be a constant expression. |
| `02-constexpr-not-guaranteed` | `constexpr` | Allows, but does not force, compile-time evaluation. |
| `03-constinit-not-ctor-const` | `constinit` | Requires constant initialization; the variable remains mutable. |

