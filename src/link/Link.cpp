//
//  Link.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Link.h"
#include "../node/Node.h"
#include "../packet/Packet.h"

Link::Link() {}

Link::Link(Node* source, Node* destination) {
    setSource(source);
    setDestination(destination);
}

Link::Link(Node* source, Node* destination, double weight) {
    setSource(source);
    setDestination(destination);
    setWeight(weight);
}

Link::~Link() {
    for (auto& packet : packetsWaiting) delete packet;
    for (auto& packet : packetsInTransmission) delete packet.first;

    // This could be also just notifying source node...
    source->removeConnection(this);
}

bool Link::setSource(Node* source) {
    if (source) {
        this->source = source;
        source->addConnection(this);
        return true;
    } else return false;
}

bool Link::setDestination(Node* destination) {
    if (destination) {
        this->destination = destination;
        return true;
    } else return false;

}

void Link::addPacket(Packet* p) { packetsWaiting.push_back(p); }

const Node* Link::getSource() const { return source; }

const Node* Link::getDestination() const { return destination; }

void Link::setWeight(double weight) {
    this->weight = weight;
}

double Link::getWeight() {
    return 1.0 / transmissionSpeed;
    //return weight;
}

void Link::setTransmissionSpeed(double speed) {
    transmissionSpeed = speed;
}

double Link::getTransmissionSpeed() {
    return transmissionSpeed;
}

void Link::setPropagationDelay(double delay) {
    propagationDelay = delay;
}

double Link::getPropagationDelay() {
    return propagationDelay;
}

const ns::Packets& Link::getPacketsWaiting() const {
    return packetsWaiting;
}

size_t Link::getQueueLength() { return packetsWaiting.size(); }

const std::map<Packet*, double>& Link::getPacketsInTransmission() const {
    return packetsInTransmission;
}

const ns::TransmissionLogType& Link::getTransmissionLog() const {
    return transmittedPackets;
}
