//
//  ns_classes.cpp
//  ns_sketch
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
    
    // add some applications running on nodes
    ns.getNode("A")->addApplications(new PacketReceiver);
    ns.getNode("A")->addApplications(new TestRouter);
    ns.getNode("B")->addApplications(new PacketReceiver);
    ns.getNode("B")->addApplications(new TestRouter);
    ns.getNode("C")->addApplications(new PacketReceiver);
    ns.getNode("C")->addApplications(new TestRouter);
    // ns.getNode("E")->addApplications(new PacketGenerator(1, ns.getAddresses()));
    ns.getNode("A")->receivePacket(new Packet("A", "C", "TESTPACKET1"));
    ns.getNode("A")->receivePacket(new Packet("A", "C", "TESTPACKET2"));

    // create some links between nodes
    ns.addLink("A", "B", 1, new ParametricLink(50.0, 100.0));
    ns.addLink("B", "C", 1, new ParametricLink(50.0, 100.0));

    // try some node deletion, some issues with this...
    // ns.removeNode("B");
    
    // set UI
    ns.setUI(new NetworkSimulatorTestUI);
    
    // run (timer has currently some hard-coded test values)
    ns.startTimer();
}
