//
//  NetworkSimulatorTestUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulatorTestUI.h"

NetworkSimulatorUI* NetworkSimulatorTestUI::createUI() { return new NetworkSimulatorTestUI(); }

void NetworkSimulatorTestUI::displayTrafficLog(ns::AddressType source, ns::AddressType destination) {
    // print traffic logs
    const auto& l = networkSimulator->getLink(source, destination);
    std::cout
        << "Transmission log for link "
        << l->getSource()->getAddress()
        << l->getDestination()->getAddress()
        << " : "
        << std::endl;
    for (auto& logEntry : l->getTransmissionLog()) {
        std::cout
        << "["
        << logEntry.first
        << ", "
        << logEntry.second / 1000.0
        << "]"
        << std::endl;
    }

}

void NetworkSimulatorTestUI::update() {

    for (auto &node : networkSimulator->getNodes()) {
        // print applications of each host node
        std::cout << "Node " << node.first << ": ";
        for(auto &app : node.second->getApplications()) {
            std::cout << "[" << app->getType() << "]";
        }
        std::cout << std::endl;
    }

    for (auto &l : networkSimulator->getLinks()) {
            // print queue lengths
            std::cout
            << "Queue length in front of link "
            <<l->getSource()->getAddress()
            << l->getDestination()->getAddress()
            << " : "
            << l->getQueueLength()
            << std::endl;
    }
    
    // separator
    std::cout
        << std::endl
        << "================================================================================"
        << std::endl;

    /* Some debugging output... */
//    std::cout
////        << type << ": "
//        << hostNode->getAddress() << " forwarded "
//        << p->getData() << " to link "
//        << targetLink->getSource()->getAddress() << "-"
//        << targetLink->getDestination()->getAddress()
//        << std::endl;

}
