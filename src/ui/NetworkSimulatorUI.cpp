//
//  NetworkSimulatorUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulatorUI.h"

NetworkSimulatorUI::NetworkSimulatorUI() {}

NetworkSimulatorUI::~NetworkSimulatorUI() {
    networkSimulator->setUI(nullptr);
}

void NetworkSimulatorUI::setNetworkSimulator(NetworkSimulator* ns) {
    networkSimulator = ns;
}
