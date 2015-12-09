//
//  PacketReceiver.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include "PacketReceiver.h"

PacketReceiver::PacketReceiver() { type = "PacketReceiver"; }

void PacketReceiver::process(double currentTime) {
    (void) currentTime;
    auto it = hostNode->getPackets().begin();
    while (it != hostNode->getPackets().end()) {
        if ((*it)->getDestination() == hostNode->getAddress()) {
            it = hostNode->getPackets().erase(it);
        } else it++;

    }
}
