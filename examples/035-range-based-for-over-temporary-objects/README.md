# 035 — Range-based `for` over temporary objects

`for (x : E)` is defined as `auto&& __range = E;` followed by the loop. Only the temporary that `E` *yields* is bound to `__range` and extended. Before C++23, temporaries created while evaluating `E` (such as `make()` in `make().items()`) are destroyed at the end of that initialization. C++23 extends the temporaries of the range-initializer (cppreference: "lifetime expansion of temporaries of range-initializer (since C++23)"), but only for the range-for itself.

| Case | Standard | Result |
| --- | --- | --- |
| `01-cxx20-temporary-in-range-init` | C++20 | `make().items()` dangles in the loop. |
| `02-cxx23-hoisted-reference` | C++23 | The same loop is fine, but pulling the initializer into `auto&& r = make().items();` dangles. |
