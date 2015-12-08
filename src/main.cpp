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

#include "network/RandomNetworkGenerator.h"

// dependency for xml parsing
#include "xml/tinyxml2.h"
#include "xml/XMLReader.h"

#include "test/Tests.h"

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
        bool args = argc > 1;
        std::string firstArg;
        
        if (args) firstArg = argv[1];
        if (firstArg != "random" && argc > 2) {
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
            if (argc == 5 && firstArg == "random") {
                RandomNetworkGenerator g(ns, std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]));
                g.generate();
            } else {
                r.load(filepath);
                std::cout << "Log: Xml file loaded" << std::endl;
                r.process();
            }
            
            
            // Let's go!
            ns.start();
        }
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }

    return result;
}
