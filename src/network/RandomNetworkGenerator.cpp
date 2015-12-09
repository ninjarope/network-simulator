//
//  RandomNetworkGenerator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 6.12.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <string>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <cmath>

#include "RandomNetworkGenerator.h"

RandomNetworkGenerator::RandomNetworkGenerator(NetworkSimulator& ns, int nodeCount, int linkCount, int genCount)
: ns(ns), applicationFactory(ns), nodeCount(nodeCount), linkCount(linkCount), genCount(genCount) {
    srand((unsigned int) time(NULL));
}

void RandomNetworkGenerator::generate() {
    const int maxNodes = std::pow(nodeCount, 2) - nodeCount;
    const int maxDistance = 1000;
    const double pi = 3.14159265;
    
    auto distance = [] (double x1, double y1, double x2, double y2) {
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    };
    
    // Node
    for (int i = 0; i < nodeCount; i++) {
        double angle = (double) i / nodeCount * (2.0 * pi);//(rand() % (int) (2.0 * pi * res)) / res;
        int r = rand() % maxDistance;
        ns.addNode(r * std::cos(angle), r * std::sin(angle), std::to_string(i));
    }
    
    // Links
    std::string source, destination;
    for (int i = 0; i < std::max(std::min(linkCount, maxNodes), nodeCount); i++) {
        source = std::to_string(i % nodeCount);
        double sx = ns.getNode(source)->getX();
        double sy = ns.getNode(source)->getY();
        double dx, dy;
        int j = 0;
        do {
            destination = std::to_string(rand() % nodeCount);
            dx = ns.getNode(destination)->getX();
            dy = ns.getNode(destination)->getY();
            j++;
            // TODO: favor nearby nodes to create more sensible networks
        } while ((destination == source || ns.getLink(source, destination) || distance(sx, sy, dx, dy) < maxDistance / 3)
                 && j < maxNodes);
        
        if (j < maxNodes) {
            // Create bidirectional link
            double speed = 1.0 + rand() % 16;
            double delay = 100;
            ns.addLink(source, destination, new ParametricLink(speed, delay));
            ns.addLink(destination, source, new ParametricLink(speed, delay));
        } else {
#if DEBUG
            std::cerr << "Could not create link!" << std::endl;
#endif
        }
    }
    
    // Routing generators
    for (auto node : ns.getNodes()) {
        node.second->addApplications(applicationFactory.create(ROUTING_GENERATOR));
    }
    
    // Packet receivers
    for (auto node : ns.getNodes()) {
        node.second->addApplications(applicationFactory.create(PACKET_RECEIVER));
    }
    
    // Packet generators
    for (int i = 0; i < std::min(nodeCount, genCount); i++) {
        std::string rate = std::to_string(1 + rand() % 100);
        std::string recipient = std::to_string(rand() % nodeCount);
        ns.getNode(std::to_string(i))
        ->addApplications(applicationFactory.create(PACKET_GENERATOR)
                          ->setParameters({rate, recipient}));
    }
    
    // Routers
    for (auto node : ns.getNodes()) {
        node.second->addApplications(applicationFactory.create(RTABLE_ROUTER));
    }
}
