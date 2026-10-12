# 084 — Implicitly deleted or suppressed special members

| Case | Rule |
| --- | --- |
| `01-dtor-suppresses-move` | A user-declared destructor suppresses the implicit move constructor, so moves silently become copies. |
| `02-move-deletes-copy` | A user-declared move constructor makes the implicit copy constructor deleted. |
