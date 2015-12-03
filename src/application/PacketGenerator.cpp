//
//  PacketGenerator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <cstdlib>

#include "PacketGenerator.h"
#include "../ns.h"

PacketGenerator::PacketGenerator() {
    type = "PacketGenerator";
    rate = 1;
    count = 1;
}

PacketGenerator::PacketGenerator(unsigned int rate) {
    type = "PacketGenerator";
    this->rate = rate;
    count = 1;
}

PacketGenerator::PacketGenerator(unsigned int rate, std::vector<ns::AddressType> destinations) {
    type = "PacketGenerator";
    this->rate = rate;
    this->destinations = destinations;
    count = 1;
}

/**
 * Generates packets and forwards them to host node.
 * */
void PacketGenerator::process(double currentTime) {
    double timeDelta = currentTime - previousTime;
    previousTime = currentTime;
    
    
    if (passedTime > 1000.0 / rate) {
        for (unsigned int i = 0; i < (unsigned int) (passedTime * rate / 1000.0); i++) {
            ns::AddressType source = hostNode->getAddress();
            ns::AddressType destination;
            if (!destinations.empty()) {
                destination = destinations[rand() % destinations.size()];
            } else {
                size_t n = hostNode->getRoutingTable().size();
                if (n > 0) {
                    auto it = hostNode->getRoutingTable().begin();
                    std::advance(it, rand() % n);
                    destination = it->first; // routing map is in form <destination, nextHop>
                } else {
                    destination = "NOT DEFINED";
                }
            }
            
            /* Generate and forward packet. */
            std::stringstream packetData;
            packetData << "PACKET " << count++ << " TO " << destination;
            hostNode->receivePacket(new Packet(source, destination, packetData.str()));
        }
        passedTime = 0.0; // reset
    }
    passedTime += timeDelta;
}
