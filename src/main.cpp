//
//  ns_classes.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include "network/NetworkSimulator.h"
#include "gui/NetworkSimulatorTestGUI.h"
#include "application/TestRouter.h"
#include "link/TestLink.h"
#include "packet/PacketGenerator.h"
#include "packet/PacketReceiver.h"

int main() {
    /* Simple test case. */

    NetworkSimulator ns;
    
    // create some nodes
    ns.addNode("A");
    ns.addNode("B");
    ns.addNode("C");
    ns.addNode("D");
    ns.addNode("E");
    
    // add some applications running on nodes
    ns.getNode("A")->addApplications(new PacketReceiver);
    ns.getNode("A")->addApplications(new TestRouter);
    ns.getNode("B")->addApplications(new PacketReceiver);
    ns.getNode("B")->addApplications(new TestRouter);
    ns.getNode("C")->addApplications(new PacketReceiver);
    ns.getNode("C")->addApplications(new TestRouter);
    ns.getNode("D")->addApplications(new PacketReceiver);
    ns.getNode("D")->addApplications(new TestRouter);
    ns.getNode("E")->addApplications(new PacketReceiver);
    ns.getNode("E")->addApplications(new TestRouter);
    ns.getNode("E")->addApplications(new PacketGenerator(1, ns.getAddresses()));
    ns.getNode("A")->receivePacket(Packet("A", "E", "TESTPACKET"));

    // create some links between nodes
    ns.addLink("A", "B", new TestLink);
    ns.addLink("A", "C", new TestLink);
    ns.addLink("B", "C", new TestLink);
    ns.addLink("C", "D", new TestLink);
    ns.addLink("D", "E", new TestLink);
    ns.addLink("E", "A", new TestLink);

    // try some node deletion, some issues with this...
    // ns.removeNode("B");
    
    // set GUI
    ns.setGUI(new NetworkSimulatorTestGUI);
    
    // run (timer has currently some hard-coded test values)
    ns.startTimer();
}
