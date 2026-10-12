# 129 — Data races and undefined behavior: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -pthread`).** TSan at `-O1` gives the same two reports from both compilers (`counter` and `payload`), with different stack frame formatting. Without a sanitizer the results differ by optimization level, 20 runs each:

| | g++ | clang++ |
| --- | --- | --- |
| `-O0` | `payload=42` every run | `payload=42` every run |
| `-O1` | `payload=42` every run | `payload=0` in 6 runs, `payload=42` in 14 |
| `-O2` | `payload=0` in 6 runs, `payload=42` in 14 | `payload=0` in 6 runs, `payload=42` in 14 |
| `-O3` | `payload=0` in 6 runs, `payload=42` in 14 | `payload=0` in 10 runs, `payload=42` in 10 |

`payload=0` means the consumer printed `payload` without observing the producer's write; the memory model permits that because there is no happens-before edge. I did not inspect the generated code to see whether the spin loop was hoisted, removed or reordered. The final `counter` value was below 200000 at `-O0` in single runs with both compilers (130487 with g++, 126484 with clang++), but 200000 at `-O2` in single runs; I did not investigate why. The point is that "it printed the right thing" is not evidence: the same source gives different answers per compiler and flag.
