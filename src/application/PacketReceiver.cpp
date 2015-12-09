//
//  PacketReceiver.cpp
//  NetworkSimulator
//

#include <iostream>

#include "PacketReceiver.h"

PacketReceiver::PacketReceiver() { type = "PacketReceiver"; }

Application* PacketReceiver::setParameters(std::vector<std::string> parameters) {
    (void) parameters;
    return this;
}
void PacketReceiver::process(double currentTime) {
    (void) currentTime;
    auto it = hostNode->getPackets().begin();
    while (it != hostNode->getPackets().end()) {
        if ((*it)->getDestination() == hostNode->getAddress()) {
            it = hostNode->getPackets().erase(it);
        } else it++;

    }
}
