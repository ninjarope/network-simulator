//
//  RandomRouter.cpp
//  NetworkSimulator
//

#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <vector>
#include <sstream>

#include "RandomRouter.h"

RandomRouter::RandomRouter() {
    type = "Random Router";
    srand((unsigned int) time(NULL));
}

Application* RandomRouter::setParameters(std::vector<std::string> parameters) {
    (void) parameters;
    return this;
}

void RandomRouter::process(double timeDelta) {
    (void) timeDelta;
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
