# 164 — `inline` functions and variables across translation units

## Why the bad code is wrong (`bad.cpp`)

A non-`inline` function defined in a header is defined once in every translation unit that includes the header, which violates the ODR: the linker sees two definitions of `twice(int)` and fails. Both compilers fail at link time: g++ `multiple definition of `twice(int)'` (`collect2: error: ld returned 1 exit status`) and clang++ the same text followed by `clang++: error: linker command failed with exit code 1`.

`inline` is mostly about linkage and the ODR, not a request to inline: it permits the same definition to appear in several translation units, and the program uses one of them (all must be identical, see 160 for what happens when they are not). Whether calls are actually expanded is decided by the optimizer.

No warning from either compiler when compiling the files separately; the error appears only when linking. Multi-file case: the extra translation units named in the `// also:` header line of `bad.cpp` are compiled and linked with it by `tools/check_examples.py` (see the `extra` key in `footguns.json`).

## The fix (`good.cpp`)

Mark the function `inline` (as `good_shared.h` does), or declare it in the header and define it in one `.cpp`. The fixed program prints `4 10`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

