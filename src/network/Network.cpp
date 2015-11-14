//
//  Network.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Network.h"

Network::Network() {}

Network::~Network() {
    for (auto& link : links) delete link;
    for (auto& node : nodes) delete node.second;
}

const std::map<nsTypes::AddressType, ApplicationNode*>& Network::getNodes() const { return nodes; }

const std::vector<Link*>& Network::getLinks() const { return links; }

ApplicationNode* Network::operator[](nsTypes::AddressType address) const {
    // TODO: return nullptr if not found
    return nodes.at(address);
}

ApplicationNode* Network::getNode(nsTypes::AddressType address) const {
    // TODO: return nullptr if not found
    return nodes.at(address);
}

const Link* Network::getLink(nsTypes::AddressType source, nsTypes::AddressType destination) const {
    // TODO: exception handling
    for (auto& link : nodes.at(source)->getConnections()) {
        if (link->getDestination()->getAddress() == destination) return link;
    }
    return nullptr;
}

bool Network::addNode(nsTypes::AddressType address) {
    nodes.insert({address, new ApplicationNode(address)});
    addresses.push_back(address);
    return true;
}

bool Network::addLink(nsTypes::AddressType source, nsTypes::AddressType destination, Link* l) {
    // TODO: exception handling
    if (l) {
        l->setSource(this->getNode(source));
        l->setDestination(this->getNode(destination));
        links.push_back(l);
        return true;
    } else return false;
}

bool Network::removeNode(nsTypes::AddressType address) {
    auto it = addresses.begin();
    while (it != addresses.end()) {
        if (*it == address) {
            addresses.erase(it);
            break;
        } else it++;
    }

    /* Erase bad links. */
    for (auto& l : links) {
        nsTypes::AddressType destination = l->getDestination()->getAddress();
        if (destination == address) {
            removeLink(l->getSource()->getAddress(), address);
        }
    }
    
    delete nodes.at(address);
    nodes.erase(address);

    return true;
}

bool Network::removeLink(nsTypes::AddressType source, nsTypes::AddressType destination) {
    auto it = links.begin();
    for (auto& l : links) {
        if (l->getSource()->getAddress() == source && l->getDestination()->getAddress() == destination) { delete l;
            links.erase(it);
            return true;
        }
        it++;
    }
    return false;
}


size_t Network::getNodeCount() {
    return nodes.size();
}

size_t Network::getLinkCount() {
    return links.size();
}

const std::vector<nsTypes::AddressType>& Network::getAddresses() const {
    return addresses;
}
