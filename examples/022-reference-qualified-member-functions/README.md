# 022 — Reference-qualified member functions

A `&` qualifier makes a member callable only on lvalues, `&&` only on rvalues, and unqualified members on both. The rules for combining them are strict, and both ways of getting them wrong are compile errors.

| Case | Error |
| --- | --- |
| `01-mixed-qualified-and-unqualified` | Overloads of one name with the same parameters must all be ref-qualified or none. |
| `02-lvalue-only-on-temporary` | Only an `&` overload exists, so calling it on a temporary has no viable function. |
