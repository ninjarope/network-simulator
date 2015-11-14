//
//  NetworkSimulatorGUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulatorGUI.h"

NetworkSimulatorGUI::NetworkSimulatorGUI() {}

NetworkSimulatorGUI::~NetworkSimulatorGUI() {
    networkSimulator->setGUI(nullptr);
}

void NetworkSimulatorGUI::setNetworkSimulator(NetworkSimulator* ns) {
    networkSimulator = ns;
}
