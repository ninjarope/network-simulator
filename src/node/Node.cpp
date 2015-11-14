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

void Node::receivePacket(Packet p) { packets.push_back(p); }

void Node::addConnection(Link* link) { connections.push_back(link); }

void Node::removeConnection(Link* link) {
    /* Requires some checking and mods... */
    auto it = connections.begin();
    if (*it && link) {
        while (it != connections.end()) {
            if (*it == link) {
                connections.erase(it);
                break;
            } else it++;
        }
    }
}

nsTypes::Connections& Node::getConnections() { return connections; }

nsTypes::PacketQueue& Node::getPackets() { return packets; }

nsTypes::AddressType Node::getAddress() { return address; }
