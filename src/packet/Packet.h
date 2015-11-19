//
//  Packet.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__Packet__
#define __NetworkSimulator__Packet__

#include "../ns.h"

/**
 * Packet that travels between nodes
 */
class Packet {
public:
    Packet();
    
    /** Construct packet that has source & destination addresses and some content (data).
        The amount of data defines packet size. */
    Packet(ns::AddressType s, ns::AddressType d, ns::PacketDataType data);

    /** Return packet ID. */
    ns::PacketIdType getID();

    /** Return source address. */
    ns::AddressType getSource();
    
    /** Return destination address. */
    ns::AddressType getDestination();
    
    /** Return packet contents. */
    ns::PacketDataType getData();
    
    /** Return size of the packet. */
    double getSize();
    
private:
    ns::PacketIdType id;
    ns::AddressType source, destination;
    ns::PacketDataType data;
    double size;
};

#endif /* defined(__NetworkSimulator__Packet__) */
