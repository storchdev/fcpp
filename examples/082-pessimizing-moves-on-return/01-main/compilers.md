# 082 — Pessimizing moves on return: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both warn with `-Wpessimizing-move` ("moving a local object in a return statement prevents copy elision") at `-O0` and `-O2`, and both print `construct` then `move`. g++ puts the column on the argument, clang++ on the `std::move` call.
