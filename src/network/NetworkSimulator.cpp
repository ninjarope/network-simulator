//  NetworkSimulator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//
#include "NetworkSimulator.h"

NetworkSimulator::NetworkSimulator() : ui(nullptr) {}
void NetworkSimulator::setUI(NetworkSimulatorUI* ui) {
    this->ui = ui;
    ui->setNetworkSimulator(this);
}

NetworkSimulator::~NetworkSimulator() { }

void NetworkSimulator::start() {
    for (auto& node : getNodes()) node.second->reset();
    for (auto& link : getLinks()) link->reset();
    startTimer();
}

void NetworkSimulator::timerCallback() {
    for (auto& node : getNodes()) node.second->run(currentTime);
    for (auto& link : getLinks()) link->run(currentTime);
    if (ui) ui->update();
}

void NetworkSimulator::updateRouting(){
    ShortestPath s1(this->nodes, this->links,this->allAvailableLinks);
    s1.alsideperm();
    // Update routings of all nodes
    for (auto& path : s1.getShortestPaths()) {
        getNode(path.front())->updateTable(path);
    }
}

void NetworkSimulator::quit() {
    stopTimer();
}
