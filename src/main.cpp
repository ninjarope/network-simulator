//
//  ns_classes.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//

#include <iostream>
#include "network/NetworkSimulator.h"
#include "ui/NetworkSimulatorTestUI.h"
#include "application/TestRouter.h"
#include "link/TestLink.h"
#include "link/ParametricLink.h"
#include "application/PacketGenerator.h"
#include "application/PacketReceiver.h"
#include "application/RandomRouter.h"

/**
 * Simple test case.
 */
int main() {


    NetworkSimulator ns;
    
    // create some nodes
    ns.addNode("A");
    ns.addNode("B");
    ns.addNode("C");
    ns.addNode("D");
    
    // add some applications running on nodes
    ns.getNode("A")->addApplications(new PacketReceiver);
    ns.getNode("A")->addApplications(new TestRouter);
    ns.getNode("B")->addApplications(new PacketReceiver);
    ns.getNode("B")->addApplications(new TestRouter);
    ns.getNode("C")->addApplications(new PacketReceiver);
    ns.getNode("C")->addApplications(new TestRouter);
    ns.getNode("D")->addApplications(new PacketReceiver);
    ns.getNode("D")->addApplications(new PacketGenerator(1, ns.getAddresses()));
    ns.getNode("D")->addApplications(new TestRouter);
    //ns.getNode("A")->receivePacket(new Packet("A", "C", "P1"));
    //ns.getNode("A")->receivePacket(new Packet("A", "C", "P2"));

    // create some links between nodes
    ns.addLink("A", "B", 1, new ParametricLink(10.0, 100.0));
    ns.addLink("B", "C", 1, new ParametricLink(5.0, 10.0));
    ns.addLink("C", "D", 1, new ParametricLink(2.0, 10.0));
    ns.addLink("D", "A", 1, new ParametricLink(1.0, 10.0));

    // try some node deletion, some issues with this...
    // ns.removeNode("B");
    
    // set UI
    ns.setUI(new NetworkSimulatorTestUI);
    
    // run (timer has currently some hard-coded test values)
    ns.startTimer();
    
    for (auto& l : ns.getLinks()) {
        // print traffic logs
        std::cout
            << "Transmission log for link "
            <<l->getSource()->getAddress()
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
        
        // print queue lengths
        std::cout
        << "Queue length in front of link "
        <<l->getSource()->getAddress()
        << l->getDestination()->getAddress()
        << " : "
        << l->getQueueLength()
        << std::endl;
        
        std::cout<< std::endl;
    }
    
}
