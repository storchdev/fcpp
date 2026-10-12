# 037 — Destructor and temporary destruction timing

Temporaries are destroyed at the end of the full-expression that created them; named locals at the end of their block, in reverse order of construction; members in reverse order of declaration (after the destructor body).

| Case | Consequence |
| --- | --- |
| `01-unnamed-lock-guard` | `std::lock_guard<std::mutex>{m};` is a temporary: it unlocks at the semicolon. |
| `02-member-destruction-order` | A member whose destructor uses another member declared *after* it sees a destroyed object. |
