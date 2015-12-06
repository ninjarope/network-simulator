//  NetworkSimulator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//
#include "NetworkSimulator.h"

NetworkSimulator::NetworkSimulator() : ui(nullptr) {
    applicationFactory = new ApplicationFactory(*this);
}

void NetworkSimulator::setUI(NetworkSimulatorUI* ui) {
    this->ui = ui;
    ui->setNetworkSimulator(this);
}

NetworkSimulator::~NetworkSimulator() {
    delete applicationFactory;
}

void NetworkSimulator::start() {
    for (auto& node : getNodes()) node.second->reset();
    for (auto& link : getLinks()) link->reset();
    updateRouting();
    startTimer();
}

void NetworkSimulator::timerCallback() {
    for (auto& node : getNodes()) node.second->run(currentTime);
    for (auto& link : getLinks()) link->run(currentTime);
    if (ui) ui->update();
}

void NetworkSimulator::quit() {
    stopTimer();
}
