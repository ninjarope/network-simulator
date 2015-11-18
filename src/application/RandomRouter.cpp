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

void RandomRouter::process(double timeDelta) {
  routingTable = hostNode->getConnections();
  connections = std::vector<Link*>();
  ns::Packets& packets = hostNode->getPackets();
  std::stringstream ss; // helper stringstream
    
  std::cout << "Entering Random router on node " << hostNode->getAddress()
      << std::endl
      << "packets: "
      << packets.size()
      << std::endl;


  // Find the connections where this node is source
  for (auto& c : routingTable) {
    if (c->getSource()->getAddress() == hostNode->getAddress()) {
//        || c->getDestination()->getAddress() == hostNode->getAddress()) {
      connections.push_back(c);
      ss << "[" << c->getSource()->getAddress() << "-" << c->getDestination()->getAddress() << "]";
    }
  }

  std::cout << "connections: " << ss.str() << std::endl;

  for (auto& p : packets) {
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
  packets.clear();
}