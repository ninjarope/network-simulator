//
//  TestLink.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "TestLink.h"

TestLink::TestLink() : Link() {}

void TestLink::run(double currentTime) {
    // Get atomic containers
    auto& packetsWaiting = *this->packetsWaiting.load();

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
