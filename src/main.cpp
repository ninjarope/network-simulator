//  ns_classes.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//
#include <iostream>
#include <string>

#include "network/NetworkSimulator.h"
#include "ui/NetworkSimulatorGUI.h"
#include "application/RandomRouter.h"
#include "application/TestRouter.h"
#include "link/TestLink.h"
#include "link/ParametricLink.h"
#include "application/PacketGenerator.h"
#include "application/PacketReceiver.h"
#include "application/TestRouter.h"

// dependency for xml parsing
#include "xml/tinyxml2.h"
#include "xml/XMLReader.h"

/**
 * Simple test case.
 */
void test1(NetworkSimulator& ns, NetworkSimulatorUI* ui);
void runUI(NetworkSimulator& ns, NetworkSimulatorUI* ui);

/**
 * test case for loading xml
 *
 * @filepath relative filepath to xml file
 */
void testXMLFileLoad(const char* filepath) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filepath);
    switch (doc.ErrorID()) {
        case 0:
            std::cout << "OK. No problem! XML File loaded." << std::endl;
            break;
        default:
            std::cout << "XML file loading error! Error code: "
                << doc.ErrorID()
                << std::endl;
    }
}

void testNodesInGui(NetworkSimulator& ns, NetworkSimulatorUI* ui) {
    // create some nodes
    ns.addNode("A");
    ns.addNode("B");
    ns.addNode("C");
    ns.addNode("D");
    ns.addNode("E");

    runUI(ns, ui);
}

void runUI(NetworkSimulator& ns, NetworkSimulatorUI* ui) {
    // Update routing tables
    // ns.update();  // comment this out if only one node or no links.. until Shortest Path gets error handling

    // run (timer has currently some hard-coded test values)

    ui->generateGraphLayout();
    ns.startTimer();
}

void testXMLReader(NetworkSimulator& ns, NetworkSimulatorUI* ui) {
    XMLReader r(ns);

    try {
        r.load("resources/in.xml");
        std::cout << "xml loaded" << std::endl;
        r.process();

        runUI(ns, ui);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
}
int main() {
    NetworkSimulator ns;
    NetworkSimulatorUI* ui = NetworkSimulatorGUI::createUI();
    ns.setUI(ui);

    testXMLReader(ns, ui);
//    testNodesInGui(ns, ui);
//    testXMLFileLoad("resources/in.xml");
//    test1(ns, ui);
}


void test1(NetworkSimulator& ns, NetworkSimulatorUI* ui) {
    // TODO Clear the out commented parts, that aren't necessary..

    // create some nodes
    ns.addNode("A");
    ns.addNode("B");
    ns.addNode("C");
    ns.addNode("D");
    ns.addNode("E");

    // add some applications running on nodes
    ns.getNode("A")->addApplications(new PacketReceiver);
    ns.getNode("A")->addApplications(new PacketGenerator(1000, ns.getAddresses()));
    ns.getNode("A")->addApplications(new TestRouter);
    ns.getNode("B")->addApplications(new PacketReceiver);
    ns.getNode("B")->addApplications(new TestRouter);
    ns.getNode("C")->addApplications(new PacketReceiver);
    ns.getNode("C")->addApplications(new PacketGenerator(800, ns.getAddresses()));
    ns.getNode("C")->addApplications(new TestRouter);
    ns.getNode("D")->addApplications(new PacketReceiver);
    ns.getNode("D")->addApplications(new TestRouter);
    ns.getNode("E")->addApplications(new PacketReceiver);
    ns.getNode("E")->addApplications(new TestRouter);

    // create some links between nodes
    ns.addLink("A", "B", new ParametricLink(1.0, 160.0, 4.0));
    ns.addLink("B", "A", new ParametricLink(1.0, 160.0, 4.0));
    
    ns.addLink("B", "C", new ParametricLink(1.0, 16.0));
    ns.addLink("C", "B", new ParametricLink(1.0, 16.0));

    ns.addLink("C", "D", new ParametricLink(1.0, 160.0));
    ns.addLink("D", "C", new ParametricLink(1.0, 160.0));
    
    ns.addLink("D", "A", new ParametricLink(2.0, 16.0));
    ns.addLink("A", "D", new ParametricLink(2.0, 16.0));

    ns.addLink("A", "E", new ParametricLink(1.0, 160.0));
    ns.addLink("E", "A", new ParametricLink(1.0, 160.0));
    
    ns.addLink("B", "E", new ParametricLink(2.0, 16.0));
    ns.addLink("E", "B", new ParametricLink(2.0, 16.0));

    ns.addLink("D", "E", new ParametricLink(2.0, 16.0));
    ns.addLink("E", "D", new ParametricLink(2.0, 16.0));


    // Update routing tables
    ns.updateRouting();
   
    // run (timer has currently some hard-coded test values)

    ui->generateGraphLayout();
    ns.start();

    // print traffic log for given node (packetID's and time stamps)
    //ui->displayTrafficLog("A", "B");
}