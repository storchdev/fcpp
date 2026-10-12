# 136 — Invalid compare-exchange memory orders

## Why the bad code is wrong (`bad.cpp`)

The failure order of `compare_exchange_*` applies to a load, so `memory_order_release` and `memory_order_acq_rel` are not valid there. Violating the requirement is undefined behavior. g++ diagnoses it at `-O0`: "invalid failure memory model ‘memory_order_release’ for ‘bool __atomic_compare_exchange_4(...)’ [-Winvalid-memory-model]", but not at `-O2`, and clang++ gives no warning at either level.

The behavior of the program is build-dependent: at `-O0` both compilers aborted on a libstdc++ assertion in `atomic_base.h` (`__is_valid_cmpexch_failure_order` failed), while at `-O2` both printed `ok = 1`. So the invalid call can fail loudly or silently.

## The fix (`good.cpp`)

Use `relaxed`, `consume`, `acquire` or `seq_cst` for the failure order. The fixed program prints `ok = 1`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

