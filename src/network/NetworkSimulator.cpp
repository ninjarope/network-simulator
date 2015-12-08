//  NetworkSimulator.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//

#include <thread>
#include "NetworkSimulator.h"
#include "debug.h"

NetworkSimulator::NetworkSimulator() : ui(nullptr) {
    applicationFactory = new ApplicationFactory(*this);
}

void NetworkSimulator::setUI(NetworkSimulatorUI* ui) {
    this->ui = ui;
    ui->setNetworkSimulator(this);
#if DEBUG
    std::cout << "UI SET: " << ui << std::endl;
#endif
}

NetworkSimulator::~NetworkSimulator() {
#if DEBUG
    std::cout << "Destroying NetworkSimulator" << std::endl;
#endif
    delete applicationFactory;
    isRunning = false;
    if (t.joinable()) {
        t.join();
    }
}

void NetworkSimulator::timerCallback() {
#if DEBUG
    std::cout << "RUNNING NS TIMER " << this << std::endl << " " << currentTime;
#endif

    const int maxThreads = 1;
    std::list<std::thread> nodeWorkers;
    std::list<std::thread> linkWorkers;
    
    auto node = getNodes().begin();
    auto link = getLinks().begin();
    auto endNode = getNodes().end();
    auto endLink = getLinks().end();
    double ct = getCurrentTime();
    
    // Start threads for nodes
    while (node != endNode) {
        for (int i = 0; i < maxThreads && node != endNode; i++) {
            nodeWorkers.push_back(std::thread(&ApplicationNode::run, node->second, ct));
            node++;
        }
        for (auto& t : nodeWorkers) t.join();
        nodeWorkers.clear();
    }

    // Start threads for links
    while (link != endLink) {
        for (int i = 0; i < maxThreads && link != endLink; i++) {
            linkWorkers.push_back(std::thread(&Link::run, *link, ct));
            link++;
        }
        for (auto& t : linkWorkers) t.join();
        linkWorkers.clear();
    }
    
    // Start thread for UI
//    if (ui) ui->update();
}

void NetworkSimulator::start() {
#if DEBUG
    std::cout << ui << std::endl;
#endif

    reset();
    t = std::thread (&NetworkSimulator::startTimer, this);
    ui->startTimer();
}

void NetworkSimulator::reset() {
    ui->generateGraphLayout();
    for (auto& node : getNodes()) node.second->reset();
    for (auto& link : getLinks()) link->reset();
    clearRouting();
}

void NetworkSimulator::quit() {
#if DEBUG
    std::cout << "TERMINATING..." << std::endl;
#endif
    ui->stopTimer();
    stopTimer();
}
