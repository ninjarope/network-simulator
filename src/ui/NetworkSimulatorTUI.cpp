//
//  NetworkSimulatorTestUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//

#include "NetworkSimulatorTUI.h"

/**
 * Enables generic UI supertype and switching of its implementation layer.
 */
NetworkSimulatorUI* NetworkSimulatorTestUI::createUI() { return new NetworkSimulatorTestUI(); }

/**
 * Main function that is called from Network Simulator.
 * Encapsulates all UI subjects.
 */
void NetworkSimulatorTestUI::update() {
    drawQueues();
    hr();
    drawApplications();
    hr();
}

/**
 * Show traffic in a link. Search the link with parameters.
 *
 * @source          a node address
 * @destination     a node address
 */
void NetworkSimulatorTestUI::displayTrafficLog(ns::AddressType source, ns::AddressType destination) {
    // print traffic logs
    const auto& l = networkSimulator->getLink(source, destination);
    std::cout
        << "Transmission log for link "
        << l->getSource()->getAddress()
        << l->getDestination()->getAddress()
        << " : "
        << std::endl;
    for (auto& logEntry : l->getTransmissionLog()) {
        std::cout
            << "["
            << logEntry.first
            << ", "
            << logEntry.second / 1000.0
            << "]"
            << std::endl;
    }

}

/**
 * Show queues of links
 */
void NetworkSimulatorTestUI::drawQueues() {
    for (auto& l : networkSimulator->getLinks()) {
        // print queue lengths
        std::cout
            << "Queue length in front of link "
            << l->getSource()->getAddress()
            << l->getDestination()->getAddress()
            << " : "
            << l->getQueueLength()
            << std::endl;
    }
}

/**
 * Show applications of all nodes
 */
void NetworkSimulatorTestUI::drawApplications() {

    std::cout << "Applications in the Network" << std::endl;

    for (auto& node : networkSimulator->getNodes()) {
        std::cout << "Node " << node.first << ": ";
        for (auto& app : node.second->getApplications()) {
            std::cout << "[" << app->getType() << "]";
        }
        std::cout << std::endl;
    }
}

/**
 * Print a horizontal line
 */
void NetworkSimulatorTestUI::hr() {
    // separator
    std::cout
        << std::endl
        << "================================================================================"
        << std::endl;
}


