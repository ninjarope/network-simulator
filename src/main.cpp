//  ns_classes.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//
#include <iostream>

#include "network/NetworkSimulator.h"
#include "ui/NetworkSimulatorGUI.h"
#include "application/RandomRouter.h"
#include "application/TestRouter.h"
#include "link/TestLink.h"
#include "link/ParametricLink.h"
#include "application/PacketGenerator.h"
#include "application/PacketReceiver.h"
#include "application/TestRouter.h"

/**
 * Simple test case.
 */
void test1(NetworkSimulator& ns, NetworkSimulatorUI* ui);

int main() {
    NetworkSimulator ns;
    NetworkSimulatorUI *ui = NetworkSimulatorGUI::createUI();
    ns.setUI(ui);

    test1(ns, ui);
}

void test1(NetworkSimulator& ns, NetworkSimulatorUI* ui) {
    // TODO Clear the out commented parts, that aren't necessary..

    // create some nodes
    ns.addNode("A");
    ns.addNode("B");
    ns.addNode("C");
    ns.addNode("D");

    // add some applications running on nodes
    ns.getNode("A")->addApplications(new PacketReceiver);
    ns.getNode("A")->addApplications(new PacketGenerator(10, ns.getAddresses()));
    ns.getNode("A")->addApplications(new RandomRouter);
    ns.getNode("B")->addApplications(new PacketReceiver);
    ns.getNode("B")->addApplications(new TestRouter);
    ns.getNode("C")->addApplications(new PacketReceiver);
    ns.getNode("C")->addApplications(new TestRouter);
    ns.getNode("D")->addApplications(new PacketReceiver);
    ns.getNode("D")->addApplications(new TestRouter);
    
    // create some links between nodes
    ns.addLink("A", "C", new ParametricLink(4.0, 16.0, 4.0));
    ns.addLink("C", "A", new ParametricLink(4.0, 16.0, 4.0));

    ns.addLink("A", "B", new ParametricLink(8.0, 16.0, 4.0));
    ns.addLink("B", "A", new ParametricLink(8.0, 16.0, 4.0));
    
    ns.addLink("B", "C", new ParametricLink(4.0, 16.0));
    ns.addLink("C", "B", new ParametricLink(4.0, 16.0));

    ns.addLink("C", "D", new ParametricLink(4.0, 16.0));
    ns.addLink("D", "C", new ParametricLink(4.0, 16.0));
    
    ns.addLink("D", "A", new ParametricLink(2.0, 16.0));
    ns.addLink("A", "D", new ParametricLink(2.0, 16.0));

    // Update routing tables
    ns.update();
   
    // run (timer has currently some hard-coded test values)

    ui->generateGraphLayout();
    ns.startTimer();

    // print traffic log for given node (packetID's and time stamps)
    //ui->displayTrafficLog("A", "B");
}