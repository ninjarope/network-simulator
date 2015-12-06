//
//  RandomNetworkGenerator.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 6.12.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__RandomNetworkGenerator__
#define __NetworkSimulator__RandomNetworkGenerator__

#include <string>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <cmath>
#include <algorithm>

#include "../ns.h"
#include "NetworkSimulator.h"
#include "../node/ApplicationNode.h"
#include "../link/ParametricLink.h"
#include "../application/ApplicationFactory.h"


class RandomNetworkGenerator {
public:
    explicit RandomNetworkGenerator(NetworkSimulator& ns, int nodeCount, int linkCount, int genCount)
        : ns(ns), applicationFactory(ns), nodeCount(nodeCount), linkCount(linkCount), genCount(genCount) {
        srand((unsigned int) time(NULL));
    }
    
    void generate() {
        // Nodes
        for (int i = 0; i < nodeCount; i++) {
            int x = rand() % 1000;
            int y = rand() % 1000;
            ns.addNode(x, y, std::to_string(i));
        }
        
        // Links
        std::string source, destination;
        for (int i = 0; i < std::max(std::min(linkCount, (int) std::pow(nodeCount, 2) - 1), nodeCount); i++) {
            source = std::to_string(i % nodeCount);
            int j = 0;
            do {
                destination = std::to_string(rand() % nodeCount);
            } while ((destination == source || ns.getLink(source, destination)) && j++ < nodeCount);
            
            // Create bidirectional link
            double speed = 1.0 + rand() % 32;
            double delay = 10.0 + (rand() % 20);
            ns.addLink(source, destination, new ParametricLink(speed, delay));
            ns.addLink(destination, source, new ParametricLink(speed, delay));
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
            std::string rate = std::to_string(1 + rand() % 1000);
            std::string recipient = std::to_string(rand() % nodeCount);
            ns.getNode(std::to_string(i))
                ->addApplications(applicationFactory.create(PACKET_GENERATOR)
                ->setParameters({rate}));
        }

        // Routers
        for (auto node : ns.getNodes()) {
            node.second->addApplications(applicationFactory.create(TEST_ROUTER));
        }

    }
    
private:
    NetworkSimulator& ns;
    const int nodeCount;
    const int linkCount;
    const int genCount;
    ApplicationFactory applicationFactory;
    
};

#endif /* defined(__NetworkSimulator__RandomNetworkGenerator__) */
