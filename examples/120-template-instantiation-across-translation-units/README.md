# 120 — Template instantiation across translation units

The examples are single files, so both cases model the multi-file problem within one translation unit.

| Case | Problem |
| --- | --- |
| `01-specialization-after-use` | A specialization declared after the primary was already implicitly instantiated. |
| `02-definition-not-visible` | A member template whose definition is not visible where it is used (link error). |

