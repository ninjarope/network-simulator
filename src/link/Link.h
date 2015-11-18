//
//  Link.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Link__
#define __ns_sketch__Link__

#include "../ns.h"
#include "../Notifiable.h"
#include "../node/Node.h"
#include "../packet/Packet.h"
#include "../node/Node.h"

/**
 * Abstract link base class. Links could destroy themselves if
 * they notice destination node has been deleted. 
 */
class Link : public Notifiable {
public:
    Link();
    
    Link(Node* source, Node* destination);
    
    virtual ~Link();
    
    /** Add packet to queue waiting for transmission. Takes ownership of the packet. */
    void addPacket(Packet* p);

    bool setSource(Node* source);
    
    bool setDestination(Node* destination);
    
    Node* getSource();

    Node* getDestination();

    /**
     * Links having speed and delay should consider time between calls
     * (timeDelta).
     */
    virtual void run(double timeDelta) = 0;
    
protected:
    Node* source;
    Node* destination;
    ns::Packets packetsWaiting;
    ns::Packets packetsInTransmission;
    double transmissionSpeed;
    double propagationDelay;
};


#endif /* defined(__ns_sketch__Link__) */
