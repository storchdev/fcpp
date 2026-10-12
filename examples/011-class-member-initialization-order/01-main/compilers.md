# 011 — Class member initialization order: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`).**

| | g++ | clang++ |
| --- | --- | --- |
| Reorder warning | `-Wreorder` | `-Wreorder-ctor` |
| Uninitialized use | `-Wuninitialized` (two warnings: `member 'Buffer::size_' is used uninitialized` and `'*this.Buffer::size_' is used uninitialized`) | `-Wuninitialized` (`field 'size_' is uninitialized when used here`) |
| Run, no sanitizer, `-O0` | `terminate called after throwing an instance of 'std::bad_alloc'` | prints `size=8` |
| Run, no sanitizer, `-O2` | prints `size=8` | prints `size=8` |
| AddressSanitizer, `-O1` | `heap-buffer-overflow` | no report (prints `size=8`) |
| UBSan, `-O1` | no report (prints `size=8`) | no report (prints `size=8`) |
| MemorySanitizer, `-O1` | not available | `use-of-uninitialized-value` inside `std::make_unique<int[]>` called from the constructor |

So the same indeterminate `size_` produced a crash, an out-of-bounds write, or nothing at all, depending on compiler and flags, which is the expected behavior for an indeterminate value. MemorySanitizer is the only sanitizer that flags it reliably across what I ran, and it needs clang++, which is why the checker builds this case with clang++.
