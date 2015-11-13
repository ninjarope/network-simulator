//
//  Network.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Network.h"

Network::Network() {}

const std::vector<std::unique_ptr<ApplicationNode>>& Network::getNodes() const { return nodes; }

const std::vector<std::unique_ptr<Link>>& Network::getLinks() const { return links; }

void Network::addNode(ApplicationNode* n) {
    nodes.push_back(std::unique_ptr<ApplicationNode>(n));
}

void Network::addLink(Link* l) { links.push_back(std::unique_ptr<Link>(l)); }
