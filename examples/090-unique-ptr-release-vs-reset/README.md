# 090 — `unique_ptr::release` vs. `reset`

| Case | Mistake |
| --- | --- |
| `01-release-leaks` | `release()` used to destroy the object: it only gives up ownership, so the object leaks. |
| `02-reset-dangles` | `reset()` destroys the object, so a raw pointer obtained earlier with `get()` dangles. |
