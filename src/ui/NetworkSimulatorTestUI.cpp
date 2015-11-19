//
//  NetworkSimulatorTestUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulatorTestUI.h"

void NetworkSimulatorTestUI::update() {

    for (auto &node : networkSimulator->getNodes()) {
        std::cout << node.first << std::endl;
        for(auto &app : node.second->getApplications()) {
            std::cout << app->getType() << std::endl;
        }
    }

    for (auto &l : networkSimulator->getLinks()) {
        (void) l;
    }

    /* Some debugging output... */
//    std::cout
////        << type << ": "
//        << hostNode->getAddress() << " forwarded "
//        << p->getData() << " to link "
//        << targetLink->getSource()->getAddress() << "-"
//        << targetLink->getDestination()->getAddress()
//        << std::endl;

}

NetworkSimulatorUI *createUI() { return new NetworkSimulatorTestUI(); }