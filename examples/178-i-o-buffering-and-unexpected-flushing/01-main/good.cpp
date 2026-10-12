// std: c++17
#include <cstdio>
#include <iostream>
#include <streambuf>

struct CountingBuf : std::streambuf {
    long syncs = 0, bytes = 0;
    int overflow(int c) override { if (c != EOF) ++bytes; return c; }
    std::streamsize xsputn(const char*, std::streamsize n) override { bytes += n; return n; }
    int sync() override { ++syncs; return 0; }
};

int main() {
    CountingBuf buf;
    std::ostream out(&buf);
    for (int i = 0; i < 100000; ++i) out << "line " << i << '\n';       // newline only
    out.flush();                                                        // flush once when the data must be visible
    std::printf("flushes = %ld, bytes = %ld\n", buf.syncs, buf.bytes);
}
