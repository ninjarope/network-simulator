//
//  ns_classes.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//

#include <iostream>

#include "network/NetworkSimulator.h"
#include "ui/NetworkSimulatorGUI.h"
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

    // initiating the MVC
    NetworkSimulator ns;
    NetworkSimulatorUI *ui = NetworkSimulatorGUI::createUI();
    ns.setUI(ui);

    // create some nodes
    ns.addNode("A");
    ns.addNode("B");
    ns.addNode("C");
    ns.addNode("D");
    ns.addNode("E");

    // add some applications running on nodes
    ns.getNode("A")->addApplications(new PacketReceiver);
    ns.getNode("A")->addApplications(new PacketGenerator(2, ns.getAddresses()));
    ns.getNode("A")->addApplications(new RandomRouter);
    ns.getNode("B")->addApplications(new PacketReceiver);
    ns.getNode("B")->addApplications(new RandomRouter);
    ns.getNode("C")->addApplications(new PacketReceiver);
    ns.getNode("C")->addApplications(new RandomRouter);
    ns.getNode("D")->addApplications(new PacketReceiver);
    ns.getNode("D")->addApplications(new RandomRouter);
    ns.getNode("E")->addApplications(new PacketReceiver);
    ns.getNode("E")->addApplications(new TestRouter);

    // create some links between nodes
    ns.addLink("A", "B", new ParametricLink(8.0, 16.0));
    ns.addLink("A", "C", new ParametricLink(4.0, 16.0));
    ns.addLink("A", "D", new ParametricLink(2.0, 16.0));
    ns.addLink("B", "E", new ParametricLink(1.0, 100.0));
    ns.addLink("C", "E", new ParametricLink(1.0, 100.0));
    ns.addLink("D", "E", new ParametricLink(1.0, 100.0));
    ns.addLink("E", "A", new ParametricLink(10.0, 100.0));

    // run (timer has currently some hard-coded test values)
    ns.startTimer();

    // print traffic log for given node (packetID's and time stamps)
    ui->displayTrafficLog("A", "B");

}
