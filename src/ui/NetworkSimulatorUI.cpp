//
//  NetworkSimulatorUI.cpp
//  NetworkSimulator
//

#include "NetworkSimulatorUI.h"

NetworkSimulatorUI::NetworkSimulatorUI() : Timer(20, 1.0, 0) {}

NetworkSimulatorUI::~NetworkSimulatorUI() {
    networkSimulator->setUI(nullptr);
}

void NetworkSimulatorUI::setNetworkSimulator(NetworkSimulator* ns) {
    networkSimulator = ns;
}


