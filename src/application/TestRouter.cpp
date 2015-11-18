//
//  TestRouter.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "TestRouter.h"
#include "../packet/Packet.h"
#include "../ns.h"

TestRouter::TestRouter() { type = "TestRouter"; }

void TestRouter::process(double timeDelta) {
    Packet* p;
    ns::AddressType packetDestination;
    ns::Packets& packets = hostNode->getPackets();
    while (!packets.empty()) {
        p = packets.front();
        packetDestination = p->getDestination();
        if (!hostNode->getConnections().empty()) {
            Link* targetLink = hostNode->getConnections().front();
            targetLink->addPacket(p);
            
            /* Some debugging output... */
            std::cout
            << hostNode->getAddress() << " forwarded "
            << p->getData() << " to link "
            << targetLink->getWeight() << "-"
            << targetLink->getDestination()->getAddress()
            << std::endl;
        }
        packets.erase(packets.begin());
    }
}
