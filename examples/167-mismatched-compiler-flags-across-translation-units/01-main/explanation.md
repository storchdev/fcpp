# 167 — Mismatched compiler flags across translation units

## Why the bad code is wrong (`bad.cpp`)

`bad_b.cpp` includes the header under `#pragma pack(push, 1)`, standing in for a different `-fpack-struct`/build configuration, so there `struct Packet { char tag; int value; }` has `value` at offset 1 and `sizeof` 5; `bad.cpp` sees the normal layout with `value` at offset 4 and `sizeof(Packet) = 8`. The same class has two different definitions in two translation units: an ODR violation (ill-formed, no diagnostic required). The writer stores `0x01020304` at offset 1; the reader loads bytes 4 to 7 and printed `value = 1 (expected 16909060), sizeof(Packet) = 8` with both compilers at `-O0` and `-O2`.

Nothing diagnoses it: each translation unit is consistent in itself, neither compiler warns under `-Wall -Wextra`, and no sanitizer I ran is involved. Macro definitions (`-DNDEBUG`), `-std=` and library ABI flags can cause the same class of mismatch. Multi-file case: the extra translation units named in the `// also:` header line of `bad.cpp` are compiled and linked with it by `tools/check_examples.py` (see the `extra` key in `footguns.json`).

## The fix (`good.cpp`)

Build all translation units with identical flags and include the shared type from one header; if a type must be packed, put the packing in the header itself so every includer agrees. The fixed program prints `value = 16909060 (expected 16909060), sizeof(Packet) = 8`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

