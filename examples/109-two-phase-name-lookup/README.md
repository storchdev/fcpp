# 109 — Two-phase name lookup

| Case | Phase that bites |
| --- | --- |
| `01-dependent-base` | Phase 1: a non-dependent name is looked up at definition and does not search a dependent base class. |
| `02-late-overload` | Phase 2: a dependent call only sees ordinary-lookup declarations from the definition context; later overloads are found only by ADL. |

