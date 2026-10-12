# 088 — `enable_shared_from_this` misuse

| Case | Mistake |
| --- | --- |
| `01-not-owned` | Calling `shared_from_this()` on an object no `shared_ptr` owns (here an automatic object). |
| `02-in-constructor` | Calling `shared_from_this()` inside the constructor, before the `shared_ptr` that will own the object exists. |
