# 110 — Argument-dependent lookup (ADL)

| Case | Effect |
| --- | --- |
| `01-hijacked-call` | An unqualified call also searches the argument's namespace and an exact match there beats a conversion in the caller's scope. |
| `02-qualified-swap` | A qualified call suppresses ADL, so the type's own overload is skipped. |

