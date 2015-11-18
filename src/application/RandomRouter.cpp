//
// Created by j on 11/17/15.
//

#include "RandomRouter.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

RandomRouter::RandomRouter() {
  type = "Random Router";
  srand(time(NULL));
}

/**
 * Empties the packet queue and routes them randomly
 */
void RandomRouter::process(double timeDelta) {
  routingTable = hostNode->getConnections();
  connections = std::vector<Link*>();
  packets = hostNode->getPackets();

  // Find the connections where this node is source
  for (auto &c : routingTable) {
    if (c->getSource()->getAddress() == hostNode->getAddress()) {

      connections.push_back(c);
    }
  }

  // forward packets
  for (auto &p : packets) {
    int randI = rand() % connections.size();
    Link* targetLink = connections[randI];

    targetLink->addPacket(p);
  }

  packets.clear();
}