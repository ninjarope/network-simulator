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
    NetworkSimulatorUI *ui = createUI();
    ns.setUI(ui);

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
    ns.getNode("D")->addApplications(new PacketGenerator(1, ns.getAddresses()));
    ns.getNode("D")->addApplications(new TestRouter);

//    // create some links between nodes
//    ns.addLink("A", "B", new TestLink);
//    ns.addLink("A", "RR", new TestLink);
//    ns.addLink("B", "RR", new TestLink);
//    ns.addLink("RR", "D", new TestLink);
//    ns.addLink("RR", "A", new TestLink);
//    ns.addLink("RR", "E", new TestLink);
//    ns.addLink("D", "E", new TestLink);
//    ns.addLink("E", "A", new TestLink);
//
//    // try some node deletion, some issues with this...
//    // ns.removeNode("B");
//
//    // set UI
//    ns.setUI(new NetworkSimulatorTestUI);
//
    // run (timer has currently some hard-coded test values)
    ns.startTimer();
}
