# 165 — Header-defined globals and linkage

| Case | What a header-defined variable does |
| --- | --- |
| `01-duplicate-definition` | `int counter = 0;` has external linkage: a definition in every includer, so linking fails. |
| `02-static-copies` | `static int counter = 0;` has internal linkage: it links, but every includer gets its own independent copy. |

Both are fixed by a C++17 `inline` variable. Both cases are multi-file: see the `// also:` header line of each `bad.cpp`.

