# 125 — Constructor exceptions and partial object destruction

| Case | Consequence |
| --- | --- |
| `01-destructor-not-run` | The throwing object's own destructor is not called, so its cleanup is skipped. |
| `02-leaked-member` | A raw owning pointer allocated earlier in the same constructor leaks. |

