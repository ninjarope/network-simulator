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
    std::cerr << "UI SET: " << ui << std::endl;
}

NetworkSimulator::~NetworkSimulator() {
    delete applicationFactory;
}

void NetworkSimulator::timerCallback() {
    
    std::cerr << "RUNNING NS TIMER " << this << std::endl << " " << currentTime;

    const int maxThreads = 32;
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
    
    std::cerr << ui << std::endl;
    
    reset();
    
    t = std::thread (&NetworkSimulator::startTimer, this);
    
    ui->startTimer();
    
}

void NetworkSimulator::reset() {
    ui->generateGraphLayout();
    for (auto& node : getNodes()) if (node.second) node.second->reset();
    for (auto& link : getLinks()) if (link) link->reset();
    clearRouting();
    resetTimer();
}

void NetworkSimulator::quit() {
    std::cerr << "TERMINATING..." << std::endl;
    ui->stopTimer();
    stopTimer();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}


