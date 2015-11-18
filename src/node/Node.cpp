//
//  Node.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Node.h"
#include "../ns.h"

Node::Node() {}

Node::Node(ns::AddressType address) : address(address) {}

Node::~Node() {
    for (auto& packet : packets) delete packet;
}

void Node::receivePacket(Packet* p) { packets.push_back(p); }

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

ns::Connections& Node::getConnections() { return connections; }

ns::Packets& Node::getPackets() { return packets; }

ns::AddressType Node::getAddress() { return address; }
