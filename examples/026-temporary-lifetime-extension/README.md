# 026 — Temporary lifetime extension

Binding a temporary directly to a reference (`const T& r = T();`, `T&& r = T();`, or a reference member in an aggregate initialized with braces) extends the temporary's lifetime to that of the reference. The exceptions are what bite: extension needs the reference to be bound directly to the temporary, in a context that grants it.

| Case | Exception |
| --- | --- |
| `01-through-function-return` | A function that returns a reference to its argument: the temporary is not bound by the caller's reference, so nothing extends it. |
| `02-new-expression` | A reference member initialized in a `new` expression: the temporary dies at the end of the full-expression. |

A third exception, a reference member bound in a constructor's mem-initializer, is entry 027.
