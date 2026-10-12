# 055 — Over-aligned allocation and packed structures

| Case | Mistake |
| --- | --- |
| `01-overaligned-malloc` | Constructing an `alignas(64)` type in `malloc` storage, which is only guaranteed aligned for `max_align_t`. |
| `02-packed-member-pointer` | Taking an ordinary pointer to a member of a packed struct; the pointer type promises alignment the member does not have. |
