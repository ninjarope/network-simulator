//
//  Packet.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Packet.h"
#include "../nsTypes.h"

Packet::Packet() {}

Packet::Packet(nsTypes::AddressType s, nsTypes::AddressType d, nsTypes::PacketDataType data)
    : source(s), destination(d), data(data) {}

nsTypes::AddressType Packet::getSource() { return source; }

nsTypes::AddressType Packet::getDestination() { return destination; }

nsTypes::PacketDataType Packet::getData() { return data; }
