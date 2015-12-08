//
//  NetworkSimulatorUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulatorUI.h"

NetworkSimulatorUI::NetworkSimulatorUI() : Timer(20, 1.0, 0) {}

NetworkSimulatorUI::~NetworkSimulatorUI() {
    networkSimulator->setUI(nullptr);
}

void NetworkSimulatorUI::setNetworkSimulator(NetworkSimulator* ns) {
    networkSimulator = ns;
}


