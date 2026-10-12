# 155 — Dangling coroutine captures and references

| Case | What dangles |
| --- | --- |
| `01-reference-parameter` | A reference parameter bound to a temporary that dies before the body runs. |
| `02-lambda-capture` | A lambda coroutine's captures, stored in the closure object rather than the coroutine frame. |

