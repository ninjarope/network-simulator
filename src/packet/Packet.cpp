//
//  Packet.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Packet.h"
#include "../ns.h"

Packet::Packet() {}

Packet::Packet(ns::AddressType s, ns::AddressType d, ns::PacketDataType data)
    : source(s), destination(d), data(data), size(data.size()) {}

ns::AddressType Packet::getSource() { return source; }

ns::AddressType Packet::getDestination() { return destination; }

ns::PacketDataType Packet::getData() { return data; }

double Packet::getSize() { return size; }