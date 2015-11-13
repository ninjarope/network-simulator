//
//  Node.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Node.h"

Node::Node() {}

Node::Node(nsTypes::AddressType address) : address(address) {}

Node::~Node() {}

void Node::receivePacket(Packet p) { packets.push(p); }

void Node::addConnection(Link* link) { connections.push_back(link); }

nsTypes::Connections& Node::getConnections() { return connections; }

nsTypes::PacketQueue& Node::getPackets() { return packets; }

nsTypes::AddressType Node::getAddress() { return address; }
