//
//  TestRouter.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__TestRouter__
#define __ns_sketch__TestRouter__

#include "Application.h"

//=============================================================
/* Example TestRouter application class. */
class TestRouter : public Application {
public:
    TestRouter() { type = "TestRouter"; }
    
    void process() override {
        // example with no routing, forward packets to "first" host node link, if any
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
    
private:
    /* Routing table. */
    nsTypes::PathsToDestinationAddress routing;
};
#endif /* defined(__ns_sketch__TestRouter__) */
