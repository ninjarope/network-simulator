//
// Created by j on 12/3/15.
//

#include <iostream>
#include "XMLReader.h"

XMLReader::XMLReader(NetworkSimulator& ns_) : ns(ns_) {
    applicationFactory = ns.getApplicationFactory();
}
XMLReader::~XMLReader() { }

void XMLReader::load(const char* filepath) {
    doc.LoadFile(filepath);

    if (doc.ErrorID() != 0) {
        // TODO Better error reporting
        throw "XML document loading error.";
    }
}

void XMLReader::process() {
    // Load first node and test for error
    // XMLHandle enables checking for nullptr's / in other words error handling
    XMLHandle docHandle(&doc);
    XMLElement* nodeElement = docHandle.FirstChild().FirstChildElement("node").ToElement();
    if (!nodeElement)
        throw "No nodes defined.";

    buildNode(nodeElement);

    // Load consequtive nodes
    XMLHandle neHandle(docHandle.FirstChild().FirstChildElement("node"));
    nodeElement = neHandle.NextSiblingElement("node").ToElement();
    while (nodeElement) {
        buildNode(nodeElement);
        XMLHandle neHandle(nodeElement);
        nodeElement = neHandle.NextSiblingElement("node").ToElement();
    }

    if (ns.getNodeCount() < 2)
        return;

    // Load links
    XMLHandle leHandle(docHandle.FirstChild().FirstChildElement("link"));
    XMLElement* linkElement = neHandle.NextSiblingElement("link").ToElement();
    while (linkElement) {
        buildLink(linkElement);
        XMLHandle leHandle(linkElement);
        linkElement = leHandle.NextSiblingElement("link").ToElement();
    }
}

void XMLReader::buildNode(XMLElement* nodeElement) {
    // make a node
    ns::AddressType address;
    double x = 0.0;
    double y = 0.0;

    std::cout << "building node "
        << address << std::endl;

    address = nodeElement->Attribute("address");
    nodeElement->QueryDoubleAttribute("x", &x);
    nodeElement->QueryDoubleAttribute("y", &y);
    ns.addNode(address);

    // add applications
    XMLHandle aeHandle(nodeElement);
    XMLElement* applicationElement = aeHandle.FirstChildElement("application").ToElement();
    while (applicationElement) {
        std::string appType = applicationElement->Attribute("type");

        if (appType == "PacketReceiver") {
            ns.getNode(address)->addApplications(
                ns.getApplicationFactory()->create(PACKET_RECEIVER));
        } else if (appType == "PacketGenerator") {
            ns.getNode(address)->addApplications(applicationFactory->create(PACKET_GENERATOR));
        } else if (appType == "RandomRouter") {
            ns.getNode(address)->addApplications(applicationFactory->create(RANDOM_ROUTER));
        } else if (appType == "TestRouter") {
            ns.getNode(address)->addApplications(applicationFactory->create(TEST_ROUTER));
        }

        XMLHandle aeHandle(applicationElement);
        applicationElement = aeHandle.NextSiblingElement("application").ToElement();
    }

}

void XMLReader::buildLink(XMLElement* e) {
    // make a link
    // Link source="A" destination="B" directed="false" type="Wireless" speed="1.0" delay="1.0" weight="1.0"/>
    ns::AddressType source = "";
    ns::AddressType destination = "";
    double speed = 0.0;
    double delay = 0.0;
    double weight = 0.0;

    // get attributes
    source = e->Attribute("source");
    destination = e->Attribute("destination");
    e->QueryDoubleAttribute("speed", &speed);
    e->QueryDoubleAttribute("delay", &delay);
    e->QueryDoubleAttribute("weight", &weight);

    ns.addLink(source, destination, new ParametricLink(speed, delay, weight));
}