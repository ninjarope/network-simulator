//
//  Packet.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Packet__
#define __ns_sketch__Packet__

#include "../ns.h"

/**
 * Packet that travels between nodes
 */
class Packet {
public:
    Packet();
    
    Packet(ns::AddressType s, ns::AddressType d, ns::PacketDataType data);
    
    ns::AddressType getSource();
    
    ns::AddressType getDestination();
    
    ns::PacketDataType getData();
    
private:
    ns::AddressType source, destination;
    ns::PacketDataType data;
};

#endif /* defined(__ns_sketch__Packet__) */
