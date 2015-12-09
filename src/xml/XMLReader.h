//
//  XMLReader.h
//  NetworkSimulator

#ifndef NS1_XMLREADER_H
#define NS1_XMLREADER_H

#include <iostream>
#include <string>
#include <sstream>

#include "../ns.h"
#include "../network/NetworkSimulator.h"
#include "../node/ApplicationNode.h"

#include "../application/ApplicationFactory.h"

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
     * Load an xml into memory
     *
     * @filepath relative path for the xml file
     * @throw exception if load is unsuccesful
     */
    void load(const char* filepath);

    /**
     * Parses the loaded xml into the network
     */
    void process();

    /** Processes the root node setting the interval, speed and endtime for the timer (of network simulator) */
    void parseRoot();

  private:
    tinyxml2::XMLDocument doc;
    NetworkSimulator& ns;
    ApplicationFactory* applicationFactory;

    /**
     * Creates nodes from xml elements and attributes and adds them to the network
     */
    void buildNode(XMLElement*);

    /**
    * Creates nodes from xml elements and attributes and adds them to the network
    */
    void buildLink(XMLElement*);

    /**
     * Creates packets from xml elements and attributes and adds them to the network
     */
    void buildPacket(XMLElement*);
    
    /**
     * Builds a string from string attribute (null checking).
     */
    std::string getStringAttribute(const char* s);

};

#endif //NS1_XMLREADER_H
