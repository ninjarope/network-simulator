//
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

NetworkSimulator::~NetworkSimulator() {}

void NetworkSimulator::timerCallback() {
    for (auto& node : getNodes()) node.second->run(currentTime);
    for (auto& link : getLinks()) link->run(currentTime);

    ui->update();
}

void NetworkSimulator::update(){
    //shortestPath s1(this->nodes, this->links);
    //s1.permute(s1.allNodes);
    //for(auto node:this->nodes){
    //  this->getNode(node)->updateTable(permute(node.first));
  //  }
    //this->getNode("A")->updateTable(Permute();
    //TODO: make loop to update all nodes
}
