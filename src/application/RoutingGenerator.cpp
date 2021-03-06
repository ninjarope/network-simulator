//
//  RoutingGenerator.cpp
//  NetworkSimulator
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
    ns::RoutingTable& hostRoutingTable = hostNode->getRoutingTable();
    
    double timeDelta = currentTime - previousTime;
    previousTime = currentTime;
    
    if (passedTime > 1000.0 / rate) {
        
        if (!hostRoutingTable.empty()) {
            for (auto connection : hostNode->getConnections()) {
                Node* neighbor = connection->getDestination();
                std::lock_guard<std::recursive_mutex> lock(neighbor->mtx);
                
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
                            }
                        } else {
                            // If host has no existing routing to destination found in neighbor's
                            // routing table, add new routing via neighbor
                            hostRoutingTable.insert({destinationAddress, {neighbor->getAddress(), newTotal}});
                        }
                    }
                } catch (std::exception) {}
            }
        } else {
            // Trivial path to node itself, which has zero weight
            ns::AddressType ownAddress = hostNode->getAddress();
            hostRoutingTable.insert({ownAddress, {ownAddress, 0.0}});
            // Initialize routing table with direct connections to neighbors
            for (auto connection : hostNode->getConnections()) {
                ns::AddressType neighborAddress = connection->getDestination()->getAddress();
                double weight = connection->getWeight();
                hostRoutingTable.insert({neighborAddress, {neighborAddress, weight}});
            }
        }
        passedTime = 0.0;
    }
    passedTime += timeDelta;
}
