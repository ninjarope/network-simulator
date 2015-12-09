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
    std::lock_guard<std::recursive_mutex> lock(mtx);

    delete applicationFactory;
    if (controllerThread.joinable()) controllerThread.join();
}

void NetworkSimulator::timerCallback() {
#if DEBUG
    std::cout << "RUNNING NS TIMER " << this << std::endl << " " << currentTime;
#endif
    std::lock_guard<std::recursive_mutex> lock(mtx);
    
    std::list<std::thread> nodeWorkers;
    std::list<std::thread> linkWorkers;
    
    auto node = getNodes().begin();
    auto link = getLinks().begin();
    auto endNode = getNodes().end();
    auto endLink = getLinks().end();
    double ct = getCurrentTime();
    
    // Start threads for nodes
    while (node != endNode) {
        for (int i = 0; i < ns::maxThreads && node != endNode; i++) {
            nodeWorkers.push_back(std::thread(&ApplicationNode::run, node->second, ct));
            node++;
        }
        for (auto& t : nodeWorkers) t.join();
        nodeWorkers.clear();
    }

    // Start threads for links
    while (link != endLink) {
        for (int i = 0; i < ns::maxThreads && link != endLink; i++) {
            linkWorkers.push_back(std::thread(&Link::run, *link, ct));
            link++;
        }
        for (auto& t : linkWorkers) t.join();
        linkWorkers.clear();
    }
}



void NetworkSimulator::start() {
#if DEBUG
    std::cout << ui << std::endl;
#endif

    reset();
    controllerThread = std::thread (&NetworkSimulator::startTimer, this);
    ui->startTimer();
    
}

void NetworkSimulator::reset() {
    std::lock_guard<std::recursive_mutex> lock(mtx);
    
    ui->generateGraphLayout();
    for (auto& node : getNodes()) if (node.second) node.second->reset();
    for (auto& link : getLinks()) if (link) link->reset();
    clearRouting();
    resetTimer();
}

void NetworkSimulator::quit() {
#if DEBUG
    std::cout << "TERMINATING..." << std::endl;
#endif
    std::lock_guard<std::recursive_mutex> lock(mtx);
    
    ui->stopTimer();
    stopTimer();
}


