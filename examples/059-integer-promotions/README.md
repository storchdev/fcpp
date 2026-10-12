# 059 — Integer promotions

| Case | Mistake |
| --- | --- |
| `01-promoted-not` | `~` and `+` on `uint8_t` produce an `int`, so the comparison and the 8-bit wraparound you expected do not happen. |
| `02-multiply` | `uint16_t * uint16_t` is multiplied as `int`; 65535 * 65535 overflows it, which is UB despite the unsigned types. |
