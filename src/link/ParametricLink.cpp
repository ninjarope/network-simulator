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
    packetToTransitTime = 0.0;
    logging = true;
}

ParametricLink::ParametricLink(double transmissionSpeed, double propagationDelay) {
    this->transmissionSpeed = transmissionSpeed;    // interval
    this->propagationDelay = propagationDelay;      // transmission time per packet
    previousTime = 0.0;
    packetToTransitTime = 0.0;
    logging = true;
}


void ParametricLink::run(double currentTime) {
    double timeDelta = currentTime - previousTime;
    previousTime = currentTime;
    std::stringstream ss;
    
    // waiting time until next packet will be picked for transmission
    if (!packetsWaiting.empty()) packetToTransitTime -= timeDelta;

    // add packets to transmission if there is some waiting...
    if (packetToTransitTime <= 0.0 && !packetsWaiting.empty()) {
            // debug output
            std::cout << "Added to transmission..." << std::endl;
            
            auto it = packetsWaiting.begin();
            // packet size determines total duration of transmission
            packetsInTransmission.insert({*it, propagationDelay});
            packetsWaiting.erase(it);

            // reset waiting time (proportional to the size of added packet)
            packetToTransitTime = transmissionSpeed * (*it)->getSize();
    }
    
    // handle packets being transmitted
    for (auto it = packetsInTransmission.begin(); it != packetsInTransmission.end();) {
        it->second -= timeDelta;
        
        // if transmission time has passed...
        if (it->second <= 0.0) {
            // deliver it to destination node
            destination->receivePacket(it->first);
            
            // add packet to transmission log {packetId, deliveryTime}
            if (logging) transmittedPackets.push_back({it->first->getID(), currentTime});
            
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
