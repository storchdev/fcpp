# f***cpp: a catalog of C++ footguns

182 interview-style C++ "gotchas", each with runnable code and a long explanation. The index is `footguns.json`; `examples/` holds one folder per entry, one subfolder per case.

Each case has:

- `bad.cpp`: the wrong code, which compiles and shows the problem (or, for ill-formed entries, fails to compile on purpose)
- `good.cpp`: the idiomatic fix
- `good.rs`: a Rust equivalent, where Rust has a real contrast
- `explanation.md`: why the bad code is wrong, why the fix works
- `compilers.md`: what g++ and clang++ did with `bad.cpp`, as a table

Entries are classified `UB` (undefined behavior), `IF` (ill-formed), `UNS` (unspecified/implementation-defined), `LOGIC`, `PERF` or `CONC`.

## Layout

| Path | Purpose |
| --- | --- |
| `footguns.json` | Index of all entries |
| `examples/` | Code and explanations |
| `tools/check_examples.py` | Builds and runs every example: `python3 -I tools/check_examples.py [NNN]` |
| `web/` | Next.js frontend that renders the catalog (`cd web && npm install && npm run dev`) |
| `raw.txt` | Original source list |
| `AGENTS.md` | Contributor rules for writing examples |

Needs `g++`, `clang++` and `rustc` to run the checker.

## License

[MIT](LICENSE)
