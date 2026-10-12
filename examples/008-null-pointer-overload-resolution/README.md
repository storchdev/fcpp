# 008 — Null pointer overload resolution

`0` and `NULL` are integer constants that happen to be convertible to pointers. `nullptr` has its own type, `std::nullptr_t`, which converts to every pointer type and nothing else.

| Case | What it shows |
| --- | --- |
| `01-overloads` | `0` selects an `int` overload, `NULL` an integer overload (or an ambiguity), and only `nullptr` selects the pointer one. |
| `02-forwarding` | once a literal `0` passes through a forwarding function it is just an `int` and no longer a null pointer constant. |
