//
//  NetworkSimulator.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulator.h"

NetworkSimulator::NetworkSimulator() {}

NetworkSimulator::NetworkSimulator(const Network&) {}

NetworkSimulator::~NetworkSimulator() {}

void NetworkSimulator::addNodes(std::vector<ApplicationNode*> nodes) {
    for (auto n : nodes) {
        network.addNode(n);
    }
}

void NetworkSimulator::addLinks(std::vector<Link*> links) {
    for (auto l : links) {
        network.addLink(l);
    }
}

const Network& NetworkSimulator::getNetworkState() const { return network; }

void NetworkSimulator::timerCallback() {
    double timeProgress = getTimerIntervalSeconds();
    for (auto& node : network.getNodes()) node->run(timeProgress);
    for (auto& link : network.getLinks()) link->run(timeProgress);
}
