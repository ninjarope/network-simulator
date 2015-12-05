//
// Created by j on 11/17/15.
//

#include "RandomRouter.h"
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <vector>
#include <sstream>

RandomRouter::RandomRouter() {
    type = "Random Router";
    srand((unsigned int) time(NULL));
}

/**
 * Empties the packet queue and routes them randomly
 */
void RandomRouter::process(double timeDelta) {
    auto& packets = hostNode->getPackets();
    
    // forward packets
    if (hostNode->getConnections().size() > 0) {
        for (auto &p : packets) {
            int randI = rand() % connections.size();
            Link* targetLink = connections[randI];
            targetLink->addPacket(p);
        }
    }
    
    packets.clear();
}