//
// Created by j on 12/4/15.
//

#ifndef NS1_TESTINGTESTS_H
#define NS1_TESTINGTESTS_H
#include "catch.h"

#include <iostream>
#include <string>
#include <sstream>

#include <chrono>
#include <thread>

#include "../ns.h"

#include "../xml/tinyxml2.h"

#include "../network/Timer.h"
#include "../network/Network.h"

#include "../network/NetworkSimulator.h"

#include "../ui/NetworkSimulatorGUI.h"
#include "../ui/NetworkSimulatorTesterUI.h"

#include "../application/PacketGenerator.h"
#include "../application/PacketReceiver.h"
#include "../application/RandomRouter.h"
#include "../application/RTableRouter.h"

#include "../link/ParametricLink.h"
#include "../link/Link.h"

#include "network/RandomNetworkGenerator.h"

/**
 * test case for loading xml
 *
 * @filepath relative filepath to xml file
 */
//TEST_CASE("All tests", "[all]") {

//    SECTION("Xml Loading") {
TEST_CASE("Xml Loading", "[xml]") {
    tinyxml2::XMLDocument doc;
    doc.LoadFile("resources/simple.xml");
    switch (doc.ErrorID()) {
        case 0:
            std::cout << "OK. No problem! XML File loaded." << std::endl;
            break;
        default:
            std::cout << "XML file loading error! Error code: "
                << doc.ErrorID()
                << std::endl;
    }
    REQUIRE(doc.ErrorID() == 0);
}

//    NetworkSimulator ns;

TEST_CASE("Test adding nodes to network", "[network]") {
//    SECTION("Test adding nodes to network") {
    NetworkSimulator ns;
    int n = 10;

// create some nodes
    for (auto i = 0; i < n; ++i) {
        ns.addNode(std::to_string(i));
    }

    REQUIRE(ns.getNodes().size() == n);
}

TEST_CASE("Test adding 10 000 nodes to network", "[network]") {
//    SECTION("Test adding nodes to network") {
    NetworkSimulator ns;
    int n = 10000;

// create some nodes
    for (auto i = 0; i < n; ++i) {
        ns.addNode(std::to_string(i));
    }

    REQUIRE(ns.getNodes().size() == n);
}

// Quite redundant and hogs up too much resources
//TEST_CASE("Test adding 10 000 000 nodes to network", "[big-network]") {
////    SECTION("Test adding nodes to network") {
//    NetworkSimulator ns;
//    int n = 10000000;
//
//// create some nodes
//    for (auto i = 0; i < n; ++i) {
//        ns.addNode(std::to_string(i));
//    }
//
//    REQUIRE(ns.getNodes().size() == n);
//}

TEST_CASE("Creating a tester ui", "[network],[ui]") {
//    SECTION("Test adding nodes to network") {
    NetworkSimulatorUI* ui = NetworkSimulatorTesterUI::createUI();

    CHECK(ui);
}

TEST_CASE("Starting a network", "[network]") {
//    SECTION("Test adding nodes to network") {
    NetworkSimulator ns;
    NetworkSimulatorUI* ui = NetworkSimulatorTesterUI::createUI();
    ns.setUI(ui);

    ns.setTimerInterval(10);
    ns.setTimerSlowdownrate(1.0);
    ns.setTimerEndTime(20);

    CHECK(ui);
}

TEST_CASE("Adding links", "[link]") {
    NetworkSimulator ns;

    std::vector < Link * > links;
    links.push_back(new ParametricLink());
    links.push_back(new ParametricLink(0.0, 0.0, 0.0));
    int n = 4;
    for (auto i = 0; i < n; ++i) {
        ns.addNode(std::to_string(i));
    }

    int i = 0;
    for (auto l : links) {
        ns::AddressType s = std::to_string(i++);
        ns::AddressType d = std::to_string(i++);
        ns.addLink(s, d, l);
    }

}

void runNs(NetworkSimulator& ns) {
    ns.setTimerInterval(4);
    ns.setTimerSlowdownrate(1.0);
    ns.setTimerEndTime(32);

    NetworkSimulator* nsptr = &ns;
    std::thread t(&NetworkSimulator::start, nsptr);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ns.quit();
    t.join();
}

std::string createRandomNetwork(NetworkSimulator& ns, int nodes, int links, int generators) {
    std::stringstream ss;
    ss << "Random network with" << std::endl
        << "Nodes: " << nodes << std::endl
        << "Links: " << links << std::endl
        << "Generators: " << generators << std::endl;

    RandomNetworkGenerator g(ns, nodes, links, generators);
    g.generate();

    return ss.str();
}

// This test mysteriously messes up the control for all the other tests..
//    SECTION("Comprehensive all around test with gui") {
TEST_CASE("Comprehensive all around test with tester ui", "[integration]") {

    std::cout << "Running integration tests / may take a few minutes.." << std::endl;

    NetworkSimulator ns;
    NetworkSimulatorUI* ui;

    SECTION("Creating the MVC Objects", "") {
        ui = NetworkSimulatorTesterUI::createUI();
        ns.setUI(ui);


        SECTION("Create some nodes", "") {
            ns.addNode("A");
            ns.addNode("B");
            ns.addNode("C");
            ns.addNode("D");
            ns.addNode("E");


            SECTION("Add some applications running on nodes", "") {
                ns.getNode("A")->addApplications(new PacketReceiver);
                ns.getNode("A")->addApplications(new PacketGenerator(1000, ns.getAddresses()));
                ns.getNode("A")->addApplications(new RTableRouter);
                ns.getNode("B")->addApplications(new PacketReceiver);
                ns.getNode("B")->addApplications(new RTableRouter);
                ns.getNode("C")->addApplications(new PacketReceiver);
                ns.getNode("C")->addApplications(new PacketGenerator(800, ns.getAddresses()));
                ns.getNode("C")->addApplications(new RTableRouter);
                ns.getNode("D")->addApplications(new PacketReceiver);
                ns.getNode("D")->addApplications(new RTableRouter);
                ns.getNode("E")->addApplications(new PacketReceiver);
                ns.getNode("E")->addApplications(new RTableRouter);


                SECTION("Create some links between nodes", "") {
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


                    SECTION("Run network simulator for a while", "") {
                        ui->generateGraphLayout();
                        runNs(ns);

                        REQUIRE(ns.getNodes().size() == 5);
                        REQUIRE(ns.getLinkCount() == 14);
                    }
                }
            }
        }
    }

    SECTION("Creating the MVC Objects for random generator", "") {
        ui = NetworkSimulatorTesterUI::createUI();
        ns.setUI(ui);

        SECTION(createRandomNetwork(ns, 10, 10, 10), "") {
            SECTION("Running the simulator", "") {
                ui->generateGraphLayout();
                runNs(ns);
            }
        }

        // Test random network changing all values 2..4
        for (auto n = 2; n < 4; ++n) {
            for (auto l = 1; l < n; ++l) {
                for (auto g = 1; g <= n; ++g) {
                    SECTION(createRandomNetwork(ns, n, l, g), "") {
                        SECTION("Running the simulator", "") {
                            ui->generateGraphLayout();
                            runNs(ns);
                        }
                    }
                }
            }
        }

        // Test random network changing values by steps 2..10
        for (auto n = 0; n < 2; ++n) {
            SECTION(createRandomNetwork(ns, 50, 50, 50), "") {
                SECTION("Running the simulator", "") {
                    ui->generateGraphLayout();
                    runNs(ns);
                }
            }
        }

        // Test random network changing values by steps 2..10
        for (auto n = 0; n < 2; ++n) {
            SECTION(createRandomNetwork(ns, 500, 500, 250), "") {
                SECTION("Running the simulator", "") {
                    ui->generateGraphLayout();
                    runNs(ns);
                }
            }
        }

//        SECTION(createRandomNetwork(ns, 10, 10, 10), "") {
//            SECTION("Running the simulator", "") {
//                ui->generateGraphLayout();
//                runNs(ns);
//            }
//        }
    }

}


#endif //NS1_TESTINGTESTS_H
