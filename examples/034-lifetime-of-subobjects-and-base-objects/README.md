# 034 — Lifetime of subobjects and base objects

While a base-class constructor runs, the object's dynamic type is the base: the derived part has not been constructed. A virtual call made there is resolved as if the object were of the base type.

| Case | Consequence |
| --- | --- |
| `01-virtual-call-in-constructor` | A virtual (non-pure) function called from the base constructor runs the base's version. Defined, but not what the author meant. |
| `02-pure-virtual-call-in-constructor` | If that function is pure virtual and the call is indirect, the behavior is undefined (observed: abort). |
