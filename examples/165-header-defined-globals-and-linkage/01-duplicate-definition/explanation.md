# 165.01 — Header-defined globals and linkage: duplicate definition

## Why the bad code is wrong (`bad.cpp`)

`int counter = 0;` in a header defines a variable with external linkage in every translation unit that includes it. The linker sees two definitions of `counter`: g++ and clang++ both fail with `multiple definition of `counter'` (g++ then prints `collect2: error: ld returned 1 exit status`, clang++ `linker command failed with exit code 1`). Compilation of each file alone has no warnings.

The usual workarounds change the semantics: `extern` in the header plus one definition elsewhere, or `static`/`const`, which silently creates one copy per file (see case 02). Multi-file case: the extra translation units named in the `// also:` header line of `bad.cpp` are compiled and linked with it by `tools/check_examples.py` (see the `extra` key in `footguns.json`).

## The fix (`good.cpp`)

Use a C++17 `inline` variable (`inline int counter = 0;`): all translation units refer to one object. The fixed program prints `counter = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

