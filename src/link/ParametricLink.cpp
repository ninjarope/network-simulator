//
//  ParametricLink.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 18.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <sstream>

#include "ParametricLink.h"

ParametricLink::ParametricLink() {
    previousTime = 0.0;
    packetToTransitTime = transmissionSpeed;
}

ParametricLink::ParametricLink(double transmissionSpeed, double propagationDelay) {
    this->transmissionSpeed = transmissionSpeed;    // interval
    this->propagationDelay = propagationDelay;      // transmission time per packet
}


void ParametricLink::run(double currentTime) {
    double timeDelta = currentTime - previousTime;
    previousTime = currentTime;
    std::stringstream ss;
    
    // waiting time until next packet will be picked for transmission
    packetToTransitTime -= timeDelta;

    // add packets to transmission
    if (packetToTransitTime <= 0.0) {
        
        // if there is packets to transmit...
        if (!packetsWaiting.empty()) {
            // debug output
            std::cout << "Added to transmission..." << std::endl;
            
            auto it = packetsWaiting.begin();
            packetsInTransmission.insert({*it, propagationDelay});
            packetsWaiting.erase(it);
        }
        
        // reset waiting time
        packetToTransitTime = transmissionSpeed;
    }
    
    // handle packets being transmitted
    for (auto it = packetsInTransmission.begin(); it != packetsInTransmission.end();) {
        it->second -= timeDelta;
        
        // if transmission time has passed...
        if (it->second <= 0.0) {
            // deliver it to destination node
            destination->receivePacket(it->first);
            
            // debug output
            std::cout
            << "Parametric link "
            << source->getAddress() << "-"
            << destination->getAddress() << " forwarded "
            << it->first->getData() << " to node "
            << destination->getAddress() << std::endl;
            
            it = packetsInTransmission.erase(it);
        } else {
            // debugging helper stringstream, format [packetData, timeToDelivery]
            ss << "[" << it->first->getData() << ", " << it->second << "]";
            
            it++;
        }
    }
    
    // debug output
    if (!packetsInTransmission.empty()) {
        std::cout
            << ss.str()
            << " in transmission on parametric link "
            << source->getAddress() << "-"
            << destination->getAddress()
            << std::endl;
    }
}
