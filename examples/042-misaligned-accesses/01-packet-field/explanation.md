# 042 — Misaligned accesses

## Why the bad code is wrong (`bad.cpp`)

An object of type `std::uint32_t` must be at an address that is a multiple of `alignof(std::uint32_t)` (4). `pkt + 1` has a 1-byte offset into an array of `unsigned char`, so the converted pointer is misaligned for `uint32_t`, and dereferencing it is undefined behavior. Merely holding enough bytes behind the pointer does not satisfy the rule.

On this x86-64 machine the program prints `16` without a sanitizer: the hardware tolerates the load, which is exactly why this pattern spreads (parsers, file formats, network code). The language rule is violated regardless of whether the hardware tolerates the load. UndefinedBehaviorSanitizer reports it on both compilers (`-std=c++17 -O1 -fsanitize=undefined`): g++ `runtime error: load of misaligned address 0x… for type 'const uint32_t', which requires 4 byte alignment`; clang++ the same with `'const std::uint32_t' (aka 'const unsigned int')`. No `-Wall -Wextra` warning; clang-tidy `cppcoreguidelines-pro-type-reinterpret-cast` flags the cast.

## The fix (`good.cpp`)

`std::memcpy(&len, pkt + 1, sizeof len)` copies the bytes into a properly aligned object; compilers lower it to an ordinary load where the target allows. Byte order is a separate concern (convert explicitly if the format is not native-endian).

## Rust (`good.rs`)

`u32::from_le_bytes([pkt[1], pkt[2], pkt[3], pkt[4]])` builds the integer from bytes, with the endianness stated. Safe Rust has no way to cast a byte pointer to `*const u32` and read it without `unsafe`.
