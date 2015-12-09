//
//  TestLink.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "TestLink.h"

TestLink::TestLink() {}

void TestLink::run(double currentTime) {
    (void) currentTime;
    while (!packetsWaiting.empty()) {
        destination->receivePacket(packetsWaiting.front());

        /* Some debugging output... */
        std::cout
            << "Link "
            << source->getAddress() << "-"
            << destination->getAddress() << " forwarded "
            << packetsWaiting.front()->getData() << " to node "
            << destination->getAddress() << std::endl;
        packetsWaiting.erase(packetsWaiting.begin());
    }
}
