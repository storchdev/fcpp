# 047 — Placement new and object replacement

Placement new constructs an object in storage you supply. The storage must be suitably aligned and large enough, and any object already there is ended (not destroyed) by the construction.

| Case | Mistake |
| --- | --- |
| `01-misaligned-arena` | A bump allocator hands out storage without honoring `alignof`. |
| `02-skipped-destructor` | Reusing storage that holds a live non-trivially-destructible object without destroying it first (a leak; defined, but wrong). |
