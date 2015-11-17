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

void RandomRouter::process(double timeDelta) {
  routingTable = hostNode->getConnections();
  connections = std::vector<Link*>();
  packets = hostNode->getPackets();

  std::cout << "Entering Random router"
      << std::endl
      << "packets: "
      << packets.size()
      << std::endl;


  // Find the connections where this node is source
  for (auto &c : routingTable) {
    if (c->getSource()->getAddress() == hostNode->getAddress()) {
//        || c->getDestination()->getAddress() == hostNode->getAddress()) {

      connections.push_back(c);
    }
  }

  std::cout << "connections: " << connections.size() << std::endl;

  for (auto &p : packets) {
    int randI = rand() % connections.size();
    Link* targetLink = connections[randI];

    /* Some debugging output... */
    std::cout
//        << type << ": "
        << hostNode->getAddress() << " forwarded "
        << p->getData() << " to link "
        << targetLink->getSource()->getAddress() << "-"
        << targetLink->getDestination()->getAddress()
        << std::endl;

    targetLink->addPacket(p);
  }

  // exhaustive
  packets.empty();
}