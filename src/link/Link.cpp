//
//  Link.cpp
//  NetworkSimulator
//

#include <iostream>

#include "Link.h"
#include "../node/Node.h"
#include "../packet/Packet.h"

Link::Link() {
    packetsWaiting.store(new ns::Packets);
    packetsInTransmission.store(new std::map<Packet*, double>);
    transmittedPackets.store(new ns::TransmissionLogType);
}

Link::Link(Node* source, Node* destination) : Link() {
    setSource(source);
    setDestination(destination);
}

Link::Link(Node* source, Node* destination, double weight) : Link() {
    setSource(source);
    setDestination(destination);
    setWeight(weight);
}

Link::~Link() {
    for (auto& packet : *packetsWaiting.load()) delete packet;
    for (auto& packet : *packetsInTransmission.load()) delete packet.first;
    
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

void Link::addPacket(Packet* p) { packetsWaiting.load()->push_back(p); }

Node* Link::getSource() { return source; }

Node* Link::getDestination() { return destination; }

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
    return *packetsWaiting.load();
}

size_t Link::getQueueLength() { return packetsWaiting.load()->size(); }

const std::map<Packet*, double>& Link::getPacketsInTransmission() const {
    return *packetsInTransmission.load();
}

const ns::TransmissionLogType& Link::getTransmissionLog() const {
    return *transmittedPackets.load();
}
