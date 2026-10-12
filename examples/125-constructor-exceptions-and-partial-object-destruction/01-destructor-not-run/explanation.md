# 125.01 — Constructor exceptions and partial object destruction: destructor not run

## Why the bad code is wrong (`bad.cpp`)

When a constructor exits by an exception, the object never became fully constructed: destructors run for the base classes and members that were already constructed, but not for the object itself. `Connection(true)` prints `open`, throws, and `~Connection` (which prints `close`) is skipped. The output was `open` / `caught: handshake failed` with both compilers at `-O0` and `-O2`.

Cleanup written in the destructor of a class that acquires several things in its constructor body is therefore incomplete on the failure path. Neither compiler warns under `-Wall -Wextra`, and no tool I ran reported it.

## The fix (`good.cpp`)

Give each resource its own RAII member (`Handle h;`): members that were fully constructed are destroyed during the unwinding. The fixed program prints `open`, `close`, `caught: handshake failed`.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.

