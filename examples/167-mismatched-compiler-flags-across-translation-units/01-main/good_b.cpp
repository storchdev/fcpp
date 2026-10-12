#include "good_packet.h"

void fill(void* p) {
    Packet* pkt = static_cast<Packet*>(p);
    pkt->tag = 'x';
    pkt->value = 0x01020304;
}
