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

NetworkSimulator::~NetworkSimulator() {}

void NetworkSimulator::timerCallback() {
    for (auto& node : getNodes()) node.second->run(currentTime);
    for (auto& link : getLinks()) link->run(currentTime);
    ui->update();
}

void NetworkSimulator::update(){
    ShortestPath s1(this->nodes, this->links,this->allAvailableLinks);
    s1.alsideperm();
    //TODO: make loop to update all nodes
    for (auto& path : s1.getShortestPaths()) {
        getNode(path.front())->updateTable(path);
        // for (auto s : path) std::cout << s;
        //std::cout << std::endl;
    }
    
}
