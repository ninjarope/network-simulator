//
//  RoutingGenerator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 6.12.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <algorithm>
#include <iostream>

#include "RoutingGenerator.h"
#include "RoutingGenerator.h"

RoutingGenerator::RoutingGenerator() {
    type = "RoutingGenerator";
    rate = 10;
}

void RoutingGenerator::process(double currentTime) {
    ns::RoutingTable hostRoutingTable = hostNode->getRoutingTable();

//    // Print rtable
//    std::cout << hostNode->getAddress() << std::endl;
//    for (auto r : hostRoutingTable) {
//        std::cout << r.first << "," << r.second.nextHop << "," << r.second.totalWeight << std::endl;
//    }
    double timeDelta = currentTime - previousTime;
    previousTime = currentTime;
    
    if (passedTime > 1000.0 / rate) {
    
        if (!hostRoutingTable.empty()) {
            for (auto connection : hostNode->getConnections()) {
                Node* neighbor = connection->getDestination();

                try {
                    // Check if in neighbor routing table has new destinations
                    for (auto entry : neighbor->getRoutingTable()) {
                        ns::AddressType destinationAddress = entry.first;
                        
                        // Cost to given destination is path cost to neighbor + associated
                        // weight in neighbor node's routing table
                        double newTotal = connection->getWeight() + entry.second.totalWeight;
                        
                        // Check if host node has routing table entry for given destination
                        auto it = hostRoutingTable.find(destinationAddress);
                        if (it != hostRoutingTable.end()) {
                            // For existing destinations, check if alternative cost is lower
                            double currentTotal = it->second.totalWeight;
                            
                            // Update routing table if lower cost routing found
                            if (newTotal < currentTotal) {
                                it->second = {neighbor->getAddress(), newTotal};
                                hostNode->updateTable(it->first, it->second);
                            }
                        } else {
                            // If host has no existing routing to destination found in neighbor's
                            // routing table, add new routing via neighbor
                            ns::TotalWeight w = {neighbor->getAddress(), newTotal};
                            hostNode->updateTable(destinationAddress, w);
                        }
                    }
                } catch (std::exception) {}
            }
        } else {
            // Trivial path to node itself, which has zero weight
            ns::AddressType ownAddress = hostNode->getAddress();
            hostNode->updateTable(ownAddress, {ownAddress, 0.0});

            // Initialize routing table with direct connections to neighbors
            for (auto connection : hostNode->getConnections()) {
                ns::AddressType neighborAddress = connection->getDestination()->getAddress();
                double weight = connection->getWeight();
                
                // Insert entry
                hostNode->updateTable(neighborAddress, {neighborAddress, weight});
            }
        }
        passedTime = 0.0;
    }
    passedTime += timeDelta;
}
