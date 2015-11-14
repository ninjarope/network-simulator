//
//  NetworkSimulator.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulator.h"

NetworkSimulator::NetworkSimulator() : gui(nullptr) {}

void NetworkSimulator::setGUI(NetworkSimulatorGUI* gui) {
    this->gui = gui;
    gui->setNetworkSimulator(this);
}

NetworkSimulator::~NetworkSimulator() {}

void NetworkSimulator::timerCallback() {
    double timeProgress = getTimerInterval();
    for (auto& node : getNodes()) node.second->run(timeProgress);
    for (auto& link : getLinks()) link->run(timeProgress);
    
    gui->update();
}
