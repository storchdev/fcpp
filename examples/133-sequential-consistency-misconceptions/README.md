# 133 — Sequential consistency misconceptions

| Case | Misconception |
| --- | --- |
| `01-store-buffering` | Release/acquire is enough to order a store before a later load of another variable. Only `seq_cst` gives a single total order. |
| `02-plain-data` | Using `seq_cst` atomics makes the program around them safe. It does not cover plain variables. |

