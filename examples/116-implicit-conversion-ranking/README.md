# 116 — Implicit conversion ranking

| Case | Ranking surprise |
| --- | --- |
| `01-template-beats-promotion` | An exact-match template outranks a non-template needing a promotion. |
| `02-literal-to-bool` | A standard conversion (pointer to `bool`) outranks a user-defined conversion (`std::string`). |

