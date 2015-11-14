//
//  PacketGenerator.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <cstdlib>

#include "PacketGenerator.h"

PacketGenerator::PacketGenerator() {
    rate = 1;
    count = 1;
}

PacketGenerator::PacketGenerator(unsigned int rate) {
    this->rate = rate;
    count = 1;
}

PacketGenerator::PacketGenerator(unsigned int rate, std::vector<nsTypes::AddressType> destinations) {
    this->rate = rate;
    this->destinations = destinations;
    count = 1;
}

/* Generates packets and adds them to host node packet queue. */
void PacketGenerator::process() {
    for (unsigned int i = 0; i < rate; i++) {
        /* Generate and add packet */
        
        nsTypes::AddressType source = hostNode->getAddress();
        nsTypes::AddressType destination;
        if (!destinations.empty()) {
            destination = destinations[rand() % destinations.size()];
        } else {
            destination = "NOT DEFINED";
        }
        
        /* Generate some data for packet... */
        std::stringstream data;
        data << "PACKET "<< count++ << " TO " << destination;
        
        Packet p(source, destination, data.str());
        hostNode->receivePacket(p);
         
    }
}
