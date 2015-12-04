//  ns_classes.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//

#define CATCH_CONFIG_RUNNER
#include "test/catch.h"

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

#include "test/Tests.h"

void runUI(NetworkSimulator& ns, NetworkSimulatorUI* ui) {
    // Update routing tables
    // ns.updateRouting();  // comment this out if only one node or no links.. until Shortest Path gets error handling

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

int main(int argc, char** argv) {
    NetworkSimulator ns;
    NetworkSimulatorUI* ui = NetworkSimulatorGUI::createUI();
    ns.setUI(ui);

    int result = 0;

    // Arguments override behaviour -> testing
    if (argc < 2) {
        testXMLReader(ns, ui);
//    testNodesInGui(ns, ui);
//    testXMLFileLoad("resources/in.xml");
//    test1(ns, ui);
    } else
        result = Catch::Session().run(argc, argv);

    return result;
}
