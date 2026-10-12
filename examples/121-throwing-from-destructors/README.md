# 121 — Throwing from destructors

| Case | Trigger of `std::terminate` |
| --- | --- |
| `01-during-unwinding` | A destructor declared `noexcept(false)` throws while another exception is propagating. |
| `02-implicit-noexcept` | A plain destructor throws: destructors are `noexcept` by default. |

