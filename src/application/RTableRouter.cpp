//
//  RTableRouter.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include "RTableRouter.h"
#include "../packet/Packet.h"
#include "../ns.h"

RTableRouter::RTableRouter() { type = "RTableRouter"; }

void RTableRouter::process(double currentTime) {
    Packet* p;
    ns::AddressType packetDestination;
    
    ns::Packets& packets = hostNode->getPackets();

    // if there is packets to processs
    while (!packets.empty()) {
        // pick first packet and read it's destination address
        p = packets.front();
        packetDestination = p->getDestination();

        //check for the destination in the routingTable and add Packet to the nexthop value from the
        //routingTable
        bool routingExists = false;

        std::lock_guard<std::recursive_mutex> lock(hostNode->mtx);
        
        for (auto entry : hostNode->getRoutingTable()) {
            if (entry.first == packetDestination) {
                for (auto l : hostNode->getConnections()) {
                    if (l->getDestination()->getAddress() == entry.second.nextHop) {
                        l->addPacket(p);
                        packets.erase(packets.begin());
                        routingExists = true;
                    }
                }
            }
        }

        if (!routingExists && !hostNode->getConnections().empty()) {
            auto& connections = hostNode->getConnections();
            int randI = rand() % connections.size();
            Link* targetLink = connections[randI];
            targetLink->addPacket(p);
            packets.erase(packets.begin());
        }
        

    }
}
