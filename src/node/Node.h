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

//=============================================================
/* Abstract base class for nodes. */
class Node {
public:
    Node() {}
    
    Node(nsTypes::AddressType address) : address(address) {}
    
    virtual ~Node() {}
    
    void receivePacket(Packet p) { packets.push(p); }
    
    void addConnection(Link* link) { connections.push_back(link); }
    
    nsTypes::Connections& getConnections() { return connections; }
    
    nsTypes::PacketQueue& getPackets() { return packets; }
    
    nsTypes::AddressType getAddress() { return address; }
    
    virtual std::string getType() const = 0;
    
    virtual void run() = 0;
    
protected:
    nsTypes::Connections connections;
    nsTypes::PacketQueue packets;
    nsTypes::AddressType address;
};

#endif /* defined(__ns_sketch__Node__) */
