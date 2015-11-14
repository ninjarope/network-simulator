//
//  Packet.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Packet__
#define __ns_sketch__Packet__

#include "../nsTypes.h"


class Packet {
public:
    Packet();
    
    Packet(nsTypes::AddressType s, nsTypes::AddressType d, nsTypes::PacketDataType data);
    
    nsTypes::AddressType getSource();
    
    nsTypes::AddressType getDestination();
    
    nsTypes::PacketDataType getData();
    
private:
    nsTypes::AddressType source, destination;
    nsTypes::PacketDataType data;
};

#endif /* defined(__ns_sketch__Packet__) */
