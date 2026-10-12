# 084.02 — Implicitly deleted or suppressed special members: move deletes copy: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17`, `-O0` and `-O2`).** Both reject `bad.cpp` at `-O0` and `-O2`:

| | g++ | clang++ |
| --- | --- | --- |
| Error | "use of deleted function ‘constexpr Handle::Handle(const Handle&)’" | "call to implicitly-deleted copy constructor of 'Handle'" |
