//
//  Node.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Node.h"
#include "../ns.h"
#include <map>
#include <iostream>

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

ns::AddressType Node::getAddress() const { return address; }

double Node::getX() { return x; }

double Node::getY() { return y; }

void Node::updateTable(std::vector<ns::AddressType> shortestPath){
    // this->routingTable.clear();
    // For given destination (last address in path) associate next node in path (check that first is this node)
    if (shortestPath.front() == this->address) {
        try {
            this->routingTable.at(shortestPath.back()) = shortestPath[1];
        } catch (std::out_of_range) {
            this->routingTable.insert({shortestPath.back(), shortestPath[1]});
        }
        std::cout << "TABLE UPDATED!" << std::endl;
    }
    
}

std::map<ns::AddressType,ns::AddressType> Node::getRoutingTable() { return routingTable; }

