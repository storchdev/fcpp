// std: c++17
// sanitize: address
// Statics are destroyed in reverse order of construction: `service` is destroyed after `log`, but its destructor uses it.
#include <cstdio>
#include <string>

struct Logger {
    std::string prefix = "a prefix long enough to need heap storage, not SSO";
    void write(const char* msg) { std::printf("%s: %s\n", prefix.c_str(), msg); }
};

struct Service {
    Service();
    ~Service();
};

Logger& log() { static Logger l; return l; }

Service service;                                   // constructed first; its constructor does not touch log()
Service::Service() {}
Service::~Service() { log().write("shutting down"); }   // log() was destroyed before this runs

int main() {
    log().write("starting");                       // first call: the Logger is constructed here, after `service`
}
