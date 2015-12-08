//
// Created by j on 12/4/15.
//

#ifndef NS1_TESTINGTESTS_H
#define NS1_TESTINGTESTS_H
#include "catch.h"

#include "../xml/tinyxml2.h"
#include "../network/Network.h"
#include "../ui/NetworkSimulatorTesterUI.h"
#include <iostream>
#include <string>

#include "../network/NetworkSimulator.h"
#include "../ui/NetworkSimulatorGUI.h"
#include "../application/RandomRouter.h"
#include "../application/TestRouter.h"
#include "../link/TestLink.h"
#include "../link/ParametricLink.h"
#include "../application/PacketGenerator.h"
#include "../application/PacketReceiver.h"
#include "../application/TestRouter.h"


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

TEST_CASE("Test adding 10 000 000 nodes to network", "[big-network]") {
//    SECTION("Test adding nodes to network") {
    NetworkSimulator ns;
    int n = 10000000;

// create some nodes
    for (auto i = 0; i < n; ++i) {
        ns.addNode(std::to_string(i));
    }

    REQUIRE(ns.getNodes().size() == n);
}

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



    CHECK(ui);
}

// This test mysteriously messes up the control for all the other tests..
//    SECTION("Comprehensive all around test with gui") {
//TEST_CASE("Comprehensive all around test with text ui", "[tui]") {
//    NetworkSimulator ns;
//
//    NetworkSimulatorUI* ui = NetworkSimulatorGUI::createUI();
//    ns.setUI(ui);
//
//// create some nodes
//    ns.addNode("A");
//    ns.addNode("B");
//    ns.addNode("C");
//    ns.addNode("D");
//    ns.addNode("E");
//
//
//// add some applications running on nodes
//    ns.getNode("A")->addApplications(new PacketReceiver);
//    ns.getNode("A")->addApplications(new PacketGenerator(1000, ns.getAddresses()));
//    ns.getNode("A")->addApplications(new TestRouter);
//    ns.getNode("B")->addApplications(new PacketReceiver);
//    ns.getNode("B")->addApplications(new TestRouter);
//    ns.getNode("C")->addApplications(new PacketReceiver);
//    ns.getNode("C")->addApplications(new PacketGenerator(800, ns.getAddresses()));
//    ns.getNode("C")->addApplications(new TestRouter);
//    ns.getNode("D")->addApplications(new PacketReceiver);
//    ns.getNode("D")->addApplications(new TestRouter);
//    ns.getNode("E")->addApplications(new PacketReceiver);
//    ns.getNode("E")->addApplications(new TestRouter);
//
//// TODO Test added applications somehow
//
//// create some links between nodes
//    ns.addLink("A", "B", new ParametricLink(1.0, 160.0, 4.0));
//    ns.addLink("B", "A", new ParametricLink(1.0, 160.0, 4.0));
//
//    ns.addLink("B", "C", new ParametricLink(1.0, 16.0));
//    ns.addLink("C", "B", new ParametricLink(1.0, 16.0));
//
//    ns.addLink("C", "D", new ParametricLink(1.0, 160.0));
//    ns.addLink("D", "C", new ParametricLink(1.0, 160.0));
//
//    ns.addLink("D", "A", new ParametricLink(2.0, 16.0));
//    ns.addLink("A", "D", new ParametricLink(2.0, 16.0));
//
//    ns.addLink("A", "E", new ParametricLink(1.0, 160.0));
//    ns.addLink("E", "A", new ParametricLink(1.0, 160.0));
//
//    ns.addLink("B", "E", new ParametricLink(2.0, 16.0));
//    ns.addLink("E", "B", new ParametricLink(2.0, 16.0));
//
//    ns.addLink("D", "E", new ParametricLink(2.0, 16.0));
//    ns.addLink("E", "D", new ParametricLink(2.0, 16.0));
//
//
//// Update routing tables
////    ns.updateRouting();
//
//// run (timer has currently some hard-coded test values)
//
////    ui->generateGraphLayout();
////    ns.start();
//
//// print traffic log for given node (packetID's and time stamps)
////ui->displayTrafficLog("A", "B");
//
//    REQUIRE(ns.getNodes().size() == 5);
//    REQUIRE(ns.getLinkCount() == 14);
//
//}
//}

#endif //NS1_TESTINGTESTS_H
