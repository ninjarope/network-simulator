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

ParametricLink::ParametricLink(double transmissionSpeed, double propagationDelay, double weight) {
    this->transmissionSpeed = transmissionSpeed;    // interval
    this->propagationDelay = propagationDelay;      // transmission time per packet
    this->weight = weight;
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
            auto it = packetsWaiting.begin();

            // packet size determines total duration of transmission
            packetsInTransmission.insert({*it, propagationDelay});
            packetsWaiting.erase(it);

            // reset waiting time (proportional to the size of added packet)
            // "time to transmit a packet == packet size / link speed"
            packetToTransitTime = (*it)->getSize() / transmissionSpeed;
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

            it = packetsInTransmission.erase(it);
        } else it++;
    }
}
