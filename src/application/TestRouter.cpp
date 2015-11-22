//
//  TestRouter.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "TestRouter.h"
#include "../packet/Packet.h"
#include "../ns.h"

TestRouter::TestRouter() { type = "TestRouter"; }

void TestRouter::process(double currentTime) {
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
        for(auto key:this->routingTable){
          if(key.first==packetDestination){
            for(auto conn:hostNode->getConnections()){
              if(conn->getDestination()->getAddress()== key.second){
                Link* targetLink = conn;
                targetLink->addPacket(p);
              }
            }
          }
        }

        /*
        // if host node has connections
        if (!hostNode->getConnections().empty()) {
            // forward packet directly to first connection
            Link* targetLink = hostNode->getConnections().front()->;
            targetLink->addPacket(p);
        }
        */
        // remove packet from queue
        packets.erase(packets.begin());
    }
}
