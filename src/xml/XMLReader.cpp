//
//  XMLReader.cpp
//  NetworkSimulator
//

#include "XMLReader.h"
#include <iostream>

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
    parseRoot();

    XMLHandle docHandle(&doc);
    XMLElement* nodeElement = docHandle.FirstChild().FirstChildElement("node").ToElement();
    
    if (!nodeElement)
        throw "No nodes defined.";

    buildNode(nodeElement);
    XMLHandle neHandle(docHandle.FirstChild().FirstChildElement("node"));
    
    // Load consequtive nodes
    nodeElement = neHandle.NextSiblingElement("node").ToElement();
    while (nodeElement) {
        buildNode(nodeElement);
        XMLHandle neHandle(nodeElement);
        nodeElement = neHandle.NextSiblingElement("node").ToElement();
    }

    // Not checking for links, if there's only one node
    if (ns.getNodeCount() < 2)
        return;

    // Load links
    XMLElement* linkElement = neHandle.NextSiblingElement("link").ToElement();
    while (linkElement) {
        buildLink(linkElement);
        XMLHandle leHandle(linkElement);
        linkElement = leHandle.NextSiblingElement("link").ToElement();
    }
    
    // Load packets
    XMLElement* packetElement = neHandle.NextSiblingElement("packet").ToElement();
    while (packetElement) {
        buildPacket(packetElement);
        XMLHandle peHandle(packetElement);
        packetElement = peHandle.NextSiblingElement("packet").ToElement();
    }
}

void XMLReader::parseRoot() {
    // Load first node and test for error
    // XMLHandle enables checking for nullptr's / in other words error handling
    XMLHandle docHandle(&doc);
    XMLElement* rootElement = docHandle.FirstChild().ToElement();
    
    if (!rootElement)
        throw "No root element defined.";

    int interval = -1;
    double slowdownrate = -1.0;
    int endTime = -1;

    rootElement->QueryIntAttribute("interval", &interval);
    
    if (interval >= 0) {
        std::cout << "Set interval: " << interval << std::endl;
        ns.setTimerInterval(interval);
    }


    rootElement->QueryDoubleAttribute("slowdownrate", &slowdownrate);
    
    if (slowdownrate >= 0.0){
        std::cout << "Set slowdownrate: " << slowdownrate << std::endl;
        ns.setTimerSlowdownrate(slowdownrate);
    }

    rootElement->QueryIntAttribute("endTime", &endTime);
    
    if (endTime >= 0) {
        std::cout << "Set endtime: " << endTime << std::endl;
        ns.setTimerEndTime(endTime);
    }
}

void XMLReader::buildNode(XMLElement* e) {
    // Variables for a node
    ns::AddressType address;
    double x = 0.0;
    double y = 0.0;

    // Read attributes to variables
    address = getStringAttribute(e->Attribute("address"));
    e->QueryDoubleAttribute("x", &x);
    e->QueryDoubleAttribute("y", &y);

    ns.addNode(x, y, address);

    // Add applications
    XMLHandle aeHandle(e); // nullptr handling
    XMLElement* applicationElement = aeHandle.FirstChildElement("application").ToElement();
    while (applicationElement) {
        std::string appType = applicationElement->Attribute("type");

        if (appType == "PacketReceiver") {
            ns.getNode(address)->
            addApplications(applicationFactory->create(ApplicationFactory::PACKET_RECEIVER));
        } else if (appType == "PacketGenerator") {
            std::vector <std::string> parameters;
            parameters.push_back(applicationElement->Attribute("rate"));

            XMLHandle pHandle(applicationElement);
            XMLElement* parameterElement = pHandle.FirstChildElement("destination").ToElement();
            while (parameterElement) {
                parameters.push_back(parameterElement->Attribute("address"));

                XMLHandle pHandle(parameterElement);
                parameterElement = pHandle.NextSiblingElement("destination").ToElement();
            }

            ns.getNode(address)->addApplications(applicationFactory
                                                     ->create(ApplicationFactory::PACKET_GENERATOR)
                                                     ->setParameters(parameters));
        } else if (appType == "RandomRouter") {
            ns.getNode(address)->
                addApplications(applicationFactory->create(ApplicationFactory::RANDOM_ROUTER));
        } else if (appType == "RTableRouter") {
            ns.getNode(address)->
                addApplications(applicationFactory->create(ApplicationFactory::RTABLE_ROUTER));
        } else if (appType == "RoutingGenerator") {
            ns.getNode(address)->
                addApplications(applicationFactory->create(ApplicationFactory::ROUTING_GENERATOR));
        }

        XMLHandle aeHandle(applicationElement); // while-loop scope
        applicationElement = aeHandle.NextSiblingElement("application").ToElement();
    }
}

void XMLReader::buildLink(XMLElement* e) {
    // make a link
    ns::AddressType source;
    ns::AddressType destination;
    bool directed = false;
    double speed = 0.0;
    double delay = 0.0;
    double weight = 0.0;

    // get attributes
    source = getStringAttribute(e->Attribute("source"));
    destination = getStringAttribute(e->Attribute("destination"));
    e->QueryBoolAttribute("directed", &directed);
    e->QueryDoubleAttribute("speed", &speed);
    e->QueryDoubleAttribute("delay", &delay);
    e->QueryDoubleAttribute("weight", &weight);

    ns.addLink(source, destination, new ParametricLink(speed, delay, weight));
    if (!directed) ns.addLink(destination, source, new ParametricLink(speed, delay, weight));
}

void XMLReader::buildPacket(XMLElement* e) {
    // Parameters
    ns::AddressType source;
    ns::AddressType destination;
    std::string data;
    double size;
    
    // Get attributes
    source = getStringAttribute(e->Attribute("source"));
    destination = getStringAttribute(e->Attribute("destination"));
    data = getStringAttribute(e->Attribute("data"));
    e->QueryDoubleAttribute("size", &size);
    
    // Packet to source node
    Node* sourceNode = ns.getNode(source);
    if (sourceNode) {
        sourceNode->receivePacket(new Packet(source, destination, data, size));
    }
}

std::string XMLReader::getStringAttribute(const char* s) {
    return std::string(s ? s : "");
}