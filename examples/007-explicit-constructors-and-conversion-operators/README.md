# 007 — `explicit` constructors and conversion operators

`explicit` removes a constructor or conversion function from *implicit* conversion, but not from every context. Direct-initialization (`T x(a)`, `T x{a}`, `static_cast<T>(a)`) still uses it. Copy-initialization (`T x = a`, function arguments, `return`) and copy-list-initialization (`T x = {a, b}`, `return {a, b}`) do not. For `explicit operator bool`, the *contextual conversion to bool* (`if`, `while`, `!`, `&&`, `||`, `?:`) uses it as well.

| Case | What it shows |
| --- | --- |
| `01-explicit-constructor` | `return {0, 0};` stops compiling when a multi-argument constructor becomes `explicit`. |
| `02-explicit-operator-bool` | leaving `explicit` off `operator bool` lets unrelated expressions (`a == b`, `a + b`) compile. |
