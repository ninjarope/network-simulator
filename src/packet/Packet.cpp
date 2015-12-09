//
//  Packet.cpp
//  NetworkSimulator
//

#include "Packet.h"
#include "../ns.h"

Packet::Packet() {}

Packet::Packet(ns::AddressType s, ns::AddressType d, ns::PacketDataType data, double size)
    : id("UUID_PLACEHOLDER"), source(s), destination(d), data(data), size(size) {}

ns::PacketIdType Packet::getID() { return id; }

ns::AddressType Packet::getSource() { return source; }

ns::AddressType Packet::getDestination() { return destination; }

ns::PacketDataType Packet::getData() { return data; }

double Packet::getSize() { return size; }
