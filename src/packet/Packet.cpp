//
//  Packet.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Packet.h"
#include "../ns.h"

Packet::Packet() {}

Packet::Packet(ns::AddressType s, ns::AddressType d, ns::PacketDataType data)
    : source(s), destination(d), data(data) {}

ns::AddressType Packet::getSource() { return source; }

ns::AddressType Packet::getDestination() { return destination; }

ns::PacketDataType Packet::getData() { return data; }
