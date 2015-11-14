//
//  PacketReceiver.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include "PacketReceiver.h"

PacketReceiver::PacketReceiver() {}

void PacketReceiver::process() {
    auto it = hostNode->getPackets().begin();
    while (it != hostNode->getPackets().end()) {
        if (it->getDestination() == hostNode->getAddress()) {
            /* Some debugging output... */
            std::cout << hostNode->getAddress() << " received " << it->getData() << std::endl;
            hostNode->getPackets().erase(it);
        }
        it++;
    }
}