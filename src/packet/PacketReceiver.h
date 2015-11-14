//
//  PacketReceiver.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__PacketReceiver__
#define __ns_sketch__PacketReceiver__

#include "../application/Application.h"

/* Packet receiver application. */
class PacketReceiver : public Application {
public:
    PacketReceiver();
    
    /* If host node is recipient of packet, receives (deletes) 
       packet. */
    void process() override;
    
private:
    unsigned int rate;
    unsigned int count;
};

#endif /* defined(__ns_sketch__PacketReceiver__) */
