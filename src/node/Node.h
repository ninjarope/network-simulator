//
//  Node.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Node__
#define __ns_sketch__Node__

#include "nsTypes.h"
#include "Packet.h"
#include "Link.h"


/* Abstract base class for nodes. */
class Node {
public:
    Node();
    
    /* Construct node and give it an address. */
    Node(nsTypes::AddressType address);
    
    virtual ~Node();
    
    /* Receive new packet and assign it to queue. */
    void receivePacket(Packet p);
    
    /* Add new (outgoing) link to other node. Links will add themselves
       to connections by calling this function when they are created. */
    void addConnection(Link* link);
    
    /* Return connections (outgoing links). */
    nsTypes::Connections& getConnections();
    
    /* Return packets currently in queue. */
    nsTypes::PacketQueue& getPackets();
    
    /* Return address of the node. */
    nsTypes::AddressType getAddress();
    
    /* Derived classes must define their type and impement this. */
    virtual std::string getType() const = 0;
    
    /* Perform some actions when clock ticks. */
    virtual void run(double timeProgress) = 0;
    
protected:
    nsTypes::Connections connections;
    nsTypes::PacketQueue packets;
    nsTypes::AddressType address;
};

#endif /* defined(__ns_sketch__Node__) */
