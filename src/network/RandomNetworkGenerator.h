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
        for (int i = 0; i < std::max(std::min(linkCount, (int) std::pow(nodeCount, 2) - 1), nodeCount); i++) {
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
            
            if (j > maxNodes) std::cerr << "Could not create link!" << std::endl;
            // Create bidirectional link
            double speed = 1.0 + rand() % 16;
            double delay = 100;
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
            std::string rate = std::to_string(1 + rand() % 100);
            std::string recipient = std::to_string(rand() % nodeCount);
            ns.getNode(std::to_string(i))
                ->addApplications(applicationFactory.create(PACKET_GENERATOR)
                ->setParameters({rate, recipient}));
        }

        // Routers
        for (auto node : ns.getNodes()) {
            node.second->addApplications(applicationFactory.create(TEST_ROUTER));
        }
    }
    
private:
    NetworkSimulator& ns;
    ApplicationFactory applicationFactory;
    const int nodeCount;
    const int linkCount;
    const int genCount;
    
};

#endif /* defined(__NetworkSimulator__RandomNetworkGenerator__) */
