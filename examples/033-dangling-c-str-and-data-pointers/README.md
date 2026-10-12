# 033 — Dangling `c_str()` and `data()` pointers

The pointer is valid only while the string is alive and unmodified. (Returning `c_str()` of a local is entry 025.)

| Case | Invalidated by |
| --- | --- |
| `01-string-modified` | A later modification that reallocates the buffer. |
| `02-temporary-string` | A temporary string destroyed at the end of the full-expression. |
