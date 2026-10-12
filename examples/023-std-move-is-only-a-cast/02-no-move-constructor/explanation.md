# 023.02 — `std::move` is only a cast: the type has no move constructor

## Why the bad code is wrong (`bad.cpp`)

When a class declares a destructor, the compiler does not implicitly declare a move constructor or move assignment (they are only implicitly declared when there is no user-declared copy operation, move operation, or destructor). The implicit copy constructor is still generated (deprecated). `Packet b = std::move(a);` yields `Packet&&`, which overload resolution can bind to `Packet(const Packet&)`, the only viable constructor. The "move" silently copies: the program prints `a=40 b=40` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17`).

Both compilers warn when asked: g++ `implicitly-declared ‘Packet::Packet(const Packet&)’ is deprecated [-Wdeprecated-copy-dtor]` and clang++ `definition of implicit copy constructor for 'Packet' is deprecated because it has a user-provided destructor [-Wdeprecated-copy-with-user-provided-dtor]`; neither is in `-Wall -Wextra`. clang-tidy `performance-move-const-arg` also reports `passing result of std::move() as a const reference argument; no move will actually happen`.

An empty `~Packet() {}` added "for debugging" or to mark a polymorphic base is a common way this appears, and it makes every container operation copy instead of move.

## The fix (`good.cpp`)

Follow the rule of zero: remove the destructor so the implicit moves are generated (`a=0 b=40` on libstdc++). If the destructor is needed, declare the moves explicitly: `Packet(Packet&&) = default; Packet& operator=(Packet&&) = default;` and the copies if they are still wanted.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
