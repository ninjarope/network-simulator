//
//  TestRouter.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "TestRouter.h"

TestRouter::TestRouter() { type = "TestRouter"; }

void TestRouter::process() {
    Packet p;
    nsTypes::AddressType packetDestination;
    nsTypes::PacketQueue& packets = hostNode->getPackets();
    while (!packets.empty()) {
        p = packets.front();
        packetDestination = p.getDestination();
        if (!hostNode->getConnections().empty()) {
            hostNode->getConnections().front()->addPacket(p);
            std::cout
            << hostNode->getAddress() << " forwarded "
            << p.getData() << " to link "
            << hostNode->getConnections().front()
            << std::endl;
        }
        packets.pop();
    }
}
