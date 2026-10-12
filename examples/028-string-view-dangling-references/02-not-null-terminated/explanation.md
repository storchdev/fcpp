# 028.02 — `std::string_view` dangling references: not null-terminated

## Why the bad code is wrong (`bad.cpp`)

A `string_view` is a pointer and a length. `data()` returns that pointer, and the range `[data(), data() + size())` is the only thing guaranteed to be readable; a terminating `'\0'` is not guaranteed (it exists only if the underlying storage happens to have one, e.g. when the view covers the end of a `std::string`). `std::printf("%s", sv.data())` passes the pointer to a function that scans for `'\0'`, so it reads past the three-byte array: undefined behavior. AddressSanitizer reports `stack-buffer-overflow` on g++ 16.2.1 and `global-buffer-overflow` on clang++ 23.1.1 (`-std=c++17 -O1`); the difference is only where each compiler places `buf`.

A quieter variant: with `std::string s = "hello world"; std::string_view sv(s);`, `std::printf("%s\n", sv.substr(0, 5).data())` printed `hello world` on both compilers (the view is five characters, but the string behind it is terminated later). No crash, wrong output, which is why this form often goes unnoticed. clang-tidy `bugprone-suspicious-stringview-data-usage` reports `result of a `data()` call may not be null terminated, provide size information to the callee to prevent potential issues` on `bad.cpp` (verified); no `-Wall -Wextra` warning from either compiler.

## The fix (`good.cpp`)

Pass the length: `%.*s` with `static_cast<int>(sv.size())`, or use iostreams. If a C API requires a terminator, construct a `std::string` (`std::string owned(sv)`) and pass `c_str()`.
