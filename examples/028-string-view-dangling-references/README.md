# 028 — `std::string_view` dangling references

A `string_view` is a non-owning (pointer, length) pair. Two distinct traps:

| Case | Trap |
| --- | --- |
| `01-from-temporary-string` | The implicit `std::string` -> `string_view` conversion lets a temporary string be passed in; the returned view outlives it. |
| `02-not-null-terminated` | `data()` is not guaranteed to be null-terminated, so C APIs that expect a C string read out of bounds. |
