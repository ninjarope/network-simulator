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
#include "../application/ApplicationFactory.h"
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
    /**
     * Constructor takes network simulator reference in order
     * to call the application factory from within it.
     */
    XMLReader(NetworkSimulator& ns_);
    ~XMLReader();

    /**
     * Load a xml into memory
     *
     * @filepath relative path for the xml file
     * @throw exception if load is unsuccesful
     */
    void load(const char* filepath);

    /**
     * Parses the loaded xml into the network
     */
    void process();

  private:
    tinyxml2::XMLDocument doc;
    NetworkSimulator& ns;
    ApplicationFactory* applicationFactory;

    /**
     * Creates nodes from xml elements and attributes and adds them to the network
     */
    void buildNode(XMLElement* nodeElement);

    /**
    * Creates nodes from xml elements and attributes and adds them to the network
    */
    void buildLink(XMLElement* e);
};

#endif //NS1_XMLREADER_H
