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

Application* PacketGenerator::setParameters(std::vector<std::string> parameters) {
    if (!parameters.empty()) {
        rate = std::stod(parameters[0]);
        parameters.erase(parameters.begin());
    }
    for (auto s : parameters) {
        destinations.push_back(s);
    };
    
    return this;
}

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
