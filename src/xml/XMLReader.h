//
// Created by j on 12/3/15.
//

#ifndef NS1_XMLREADER_H
#define NS1_XMLREADER_H

#include <iostream>
#include <string>
#include <sstream>

#include "../ns.h"
#include "../network/NetworkSimulator.h"
#include "../node/ApplicationNode.h"

// TODO This shit should be handled with a factory..
//#include "../application/ApplicationFactory.h"
#include "../application/PacketReceiver.h"
#include "../application/PacketGenerator.h"
#include "../application/RandomRouter.h"
#include "../application/TestRouter.h"

#include "../link/ParametricLink.h"

// dependency for xml parsing
#include "tinyxml2.h"

// Reducing the risk of carpal tunnel syndrome
using namespace tinyxml2;

/**
 * Handles the parsing of an xml into a network graph
 */
class XMLReader {
public:
    XMLReader(NetworkSimulator& ns_) : ns(ns_) { }
    ~XMLReader() { }
    
    /**
     * Load a xml into memory
     *
     * @filepath relative path for the xml file
     * @throw exception if load is unsuccesful
     */
    void load(const char* filepath) {
        doc.LoadFile(filepath);
        
        if (doc.ErrorID() != 0) {
            // TODO Better error reporting
            throw "XML document loading error.";
        }
    }
    
    void process() {
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
    
private:
    tinyxml2::XMLDocument doc;
    NetworkSimulator& ns;
//    ApplicationFactory applicationFactory;
    
    /**
     * Creates nodes from xml elements and attributes and adds them to the network
     */
    void buildNode(XMLElement* nodeElement) {
        // make a node
        ns::AddressType address;
        double x = 0.0;
        double y = 0.0;
        
        address = std::string(nodeElement->Attribute("address"));
        nodeElement->QueryDoubleAttribute("x", &x);
        nodeElement->QueryDoubleAttribute("y", &y);
        
        std::cout << "building node "
        << address << std::endl;
        
        ns.addNode(x, y, address);
        
        // add applications
        XMLHandle aeHandle(nodeElement);
        XMLElement* applicationElement = aeHandle.FirstChildElement("application").ToElement();
        while (applicationElement) {
            std::string appType = applicationElement->Attribute("type");
//            std::vector<std::string> parameters;
//            std::stringstream ss;
//            int i = 0;
//            
//            while (true) {
//                char s[2];
//                s[0] = 'p';
//                s[1] = ;
//                ss << "p" << i++;
//                if (!ss.str()) parameters.push_back(applicationElement->Attribute(ss.str()));
//                else break;
//            };
            
            if (appType == "PacketReceiver") {
                ns.getNode(address)->addApplications(new PacketReceiver);
            } else if (appType == "RandomRouter") {
                ns.getNode(address)->addApplications(new RandomRouter);
            } else if (appType == "PacketGenerator") {
                double rate = 0.0;
                applicationElement->QueryDoubleAttribute("rate", &rate);
                ns.getNode(address)->addApplications(new PacketGenerator(rate));
            }
            
            XMLHandle aeHandle(applicationElement);
            applicationElement = aeHandle.NextSiblingElement("application").ToElement();
        }
        
    }
    
    /**
     * Creates nodes from xml elements and attributes and adds them to the network
     */
    void buildLink(XMLElement* e) {
        // make a link
        // Link source="A" destination="B" directed="false" type="Wireless" speed="1.0" delay="1.0" weight="1.0"/>
        ns::AddressType source = "";
        ns::AddressType destination = "";
        bool directed = false;
        double speed = 0.0;
        double delay = 0.0;
        double weight = 0.0;
        
        // get attributes
        source = e->Attribute("source");
        destination = e->Attribute("destination");
        e->QueryBoolAttribute("directed", &directed);
        e->QueryDoubleAttribute("speed", &speed);
        e->QueryDoubleAttribute("delay", &delay);
        e->QueryDoubleAttribute("weight", &weight);
        
        ns.addLink(source, destination, new ParametricLink(speed, delay, weight));
        if (!directed) ns.addLink(destination, source, new ParametricLink(speed, delay, weight));
    }
};

#endif //NS1_XMLREADER_H
