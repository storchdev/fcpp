# 033.01 — Dangling `c_str()` and `data()` pointers: modification

## Why the bad code is wrong (`bad.cpp`)

`c_str()` and `data()` return a pointer into the string's current buffer. Any operation that modifies the string may reallocate it (and the standard lets a non-const modification invalidate the pointer anyway). `path += "…long suffix…"` exceeds the small-string capacity, so the string allocates a larger buffer and frees the old one; `c` still points at the old one. Printing it is undefined behavior. AddressSanitizer reports `heap-use-after-free` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -O1`).

No `-Wall -Wextra` warning from either compiler. clang-tidy `clang-analyzer-cplusplus.InnerPointer` reports `Inner pointer of container used after re/deallocation` (verified).

(Returning `c_str()` of a local string is entry 025; case 02 here is the temporary.)

## The fix (`good.cpp`)

Take the pointer after the last modification and use it before the next one, or re-obtain it each time. Prefer passing `const std::string&` or `std::string_view` and calling `c_str()` at the C API boundary.
