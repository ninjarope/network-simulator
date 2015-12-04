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
    // TODO fix this or clear comments
    // Update routing tables
    ns.updateRouting();  // comment this out if only one node or no links.. until Shortest Path gets error handling

    // run (timer has currently some hard-coded test values)

    ui->generateGraphLayout();
    ns.startTimer();
}

int main(int argc, char** argv) {
    NetworkSimulator ns;
    NetworkSimulatorUI* ui = NetworkSimulatorGUI::createUI();
    ns.setUI(ui);

    XMLReader r(ns);

    // for testing
    int result = 0;

    // Relative path for xml file
    const char* filepath = "";

    // Load configuration for network and launch UI
    try {
        // Arguments override behaviour -> testing
        if (argc > 2) {
            // Run tests
            result = Catch::Session().run(argc, argv);
        } else {
            // Define default case or use file path from arguments
            if (argc == 2) {
                filepath = argv[1];
            } else {
                // This is documented in README.md so change it if you change this
                filepath = "resources/default.xml";
            }

            // load xml
            r.load(filepath);
            std::cout << "Log: Xml file loaded" << std::endl;
            r.process();

            // Graphics!
            runUI(ns, ui);
        }
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    return result;
}
