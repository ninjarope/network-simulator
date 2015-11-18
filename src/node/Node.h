//
//  Node.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Node__
#define __ns_sketch__Node__

#include "../ns.h"
#include "../Notifiable.h"
#include "../packet/Packet.h"
#include "../link/Link.h"


/** Abstract base class for nodes. */
class Node : public Notifiable {
public:
    Node();
    
    /** Construct node and give it an address. */
    Node(ns::AddressType address);
    
    virtual ~Node();
    
    /** Receive new packet and assign it to queue. Takes ownership of the packet. */
    void receivePacket(Packet* p);
    
    /** Add new (outgoing) link to other node. Links will add themselves
       to connections by calling this function when they are created. */
    void addConnection(Link* link);

    /** Remove outgoing connection. Links can call this when deleting themselves. */
    void removeConnection(Link* link);

    /** Return connections (outgoing links). */
    ns::Connections& getConnections();
    
    /** Return packets currently in queue. */
    ns::Packets& getPackets();
    
    /** Return address of the node. */
    ns::AddressType getAddress();
    
    /** Derived classes must define their type and implement this. */
    virtual std::string getType() const = 0;
    
    /** Perform some actions when clock ticks. */
    virtual void run(double timeDelta) = 0;
    
protected:
    ns::Connections connections;
    ns::Packets packets;
    ns::AddressType address;
};

#endif /** defined(__ns_sketch__Node__) */
