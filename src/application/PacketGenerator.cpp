//
//  PacketGenerator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
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
    for (unsigned int i = 0; i < rate; i++) {
        ns::AddressType source = hostNode->getAddress();
        ns::AddressType destination;
        if (!destinations.empty()) {
            destination = destinations[rand() % destinations.size()];
        } else {
            destination = "NOT DEFINED";
        }
        
        /* Generate and forward packet. */
        std::stringstream packetData;
        packetData << "PACKET " << count++ << " TO " << destination;
        hostNode->receivePacket(new Packet(source, destination, packetData.str()));
         
    }
}
