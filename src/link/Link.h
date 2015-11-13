//
//  Link.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Link__
#define __ns_sketch__Link__

#include "nsTypes.h"
#include "Node.h"
#include "Packet.h"

//=============================================================
/* Abstract link base class. */
class Link {
public:
    Link() {}
    
    Link(Node* source, Node* destination) {
        this->source = source;
        this->destination = destination;
        source->addConnection(this);
    }
    
    virtual ~Link() {}
    
    /* Add packet to queue waiting for transmission. */
    void addPacket(Packet p) { packetsWaiting.push(p); }
    
    virtual void run() = 0;
    
protected:
    Node* source;
    Node* destination;
    nsTypes::PacketQueue packetsWaiting;
    std::vector<Packet> packetsInTransmission;
    double transmissionSpeed;
    double propagationDelay;
};


#endif /* defined(__ns_sketch__Link__) */
