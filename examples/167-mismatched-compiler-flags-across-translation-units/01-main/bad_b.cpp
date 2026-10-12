#pragma pack(push, 1)                              // stands in for -fpack-struct or a different build configuration
#include "bad_packet.h"
#pragma pack(pop)

void fill(void* p) {
    Packet* pkt = static_cast<Packet*>(p);
    pkt->tag = 'x';
    pkt->value = 0x01020304;                       // written at offset 1 in this translation unit's layout
}
