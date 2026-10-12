# 166 — ABI incompatibility

## Why the bad code is wrong (`bad.cpp`)

`bad_lib.cpp` defines `_GLIBCXX_USE_CXX11_ABI` as `0` before including `<string>`, so it is compiled against libstdc++'s old `std::string` ABI (the symbol it exports is `greeting()`), while `bad.cpp` uses the default new ABI and refers to `greeting[abi:cxx11]()`. In this case the mismatch is caught by the linker: both compilers report `undefined reference to `greeting[abi:cxx11]()'` (`nm -C` of the objects shows `greeting()` in `bad_lib.o` and `greeting[abi:cxx11]()` in the good one). That is the lucky outcome: the library ABI changed the mangled name. Mismatches that do not change a symbol name (struct layout, calling convention, different standard-library builds) link fine and fail at run time; see 167 for a layout example. Multi-file case: the extra translation units named in the `// also:` header line of `bad.cpp` are compiled and linked with it by `tools/check_examples.py` (see the `extra` key in `footguns.json`).

## The fix (`good.cpp`)

Build every translation unit and every library of the program with the same compiler, standard library and ABI flags (the fixed program drops the macro). For a stable boundary use a C interface (`extern "C"`) or a versioned ABI. The fixed program prints `hello`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

