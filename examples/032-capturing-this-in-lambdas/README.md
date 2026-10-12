# 032 — Capturing `this` in lambdas

`[=]` copies local variables, but members are reached through `this`, and what is captured is the pointer. Two consequences:

| Case | Consequence |
| --- | --- |
| `01-closure-outlives-object` | The closure holds a raw pointer to the object; if the object dies first, the call is a use after free. |
| `02-copy-default-captures-this` | `[=]` does not snapshot members: later changes to the object are visible inside the closure. |

(C++20 deprecates the implicit `this` capture by `[=]`.)
