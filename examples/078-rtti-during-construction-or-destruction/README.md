# 078 — RTTI during construction or destruction

| Case | Mistake |
| --- | --- |
| `01-typeid-in-ctor` | `typeid` and `dynamic_cast` inside a base constructor see the base class, not the most-derived one (defined, but surprising). |
| `02-unconstructed-base` | `typeid` on a polymorphic base subobject that has not been constructed yet is undefined behavior. |
