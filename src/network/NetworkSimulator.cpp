//  NetworkSimulator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//

#include <thread>
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

void NetworkSimulator::timerCallback() {
    const int threads = 32;
    std::vector<std::thread> nodeWorkers;
    std::vector<std::thread> linkWorkers;
    
    auto node = getNodes().begin();
    auto link = getLinks().begin();
    auto endNode = getNodes().end();
    auto endLink = getLinks().end();
    double ct = getCurrentTime();
    
    // Start threads for nodes
    while (node != endNode) {
        for (int i = 0; i < threads && node != endNode; i++) {
            nodeWorkers.push_back(std::thread(&ApplicationNode::run, node->second, ct));
            node++;
        }
        for (auto& t : nodeWorkers) t.join();
        nodeWorkers.clear();
    }

    // Start threads for links
    while (link != endLink) {
        for (int i = 0; i < threads && link != endLink; i++) {
            linkWorkers.push_back(std::thread(&Link::run, *link, ct));
            link++;
        }
        for (auto& t : linkWorkers) t.join();
        linkWorkers.clear();
    }
    
    // Start thread for UI
    if (ui) ui->update();
}

void NetworkSimulator::restart() {
    ui->generateGraphLayout();
    for (auto& node : getNodes()) node.second->reset();
    for (auto& link : getLinks()) link->reset();
    clearRouting();
    startTimer();
}

void NetworkSimulator::quit() {
    stopTimer();
}
