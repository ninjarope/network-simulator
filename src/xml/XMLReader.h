//
// Created by j on 12/3/15.
//

#ifndef NS1_XMLREADER_H
#define NS1_XMLREADER_H


#include "../ns.h"
#include "../network/NetworkSimulator.h"

// dependency for xml parsing
#include "xml/tinyxml2.h"


using namespace tinyxml2;

class XMLReader {
  public:
    bool load(NetworkSimulator& ns, const char* filepath) {
        bool failed = true;
        tinyxml2::XMLDocument doc;
        doc.LoadFile(filepath);

        switch (doc.ErrorID()) {
            case 0:
                std::cout << "OK. No problem! XML File loaded." << std::endl;
                failed = false;
                break;
            default:
                std::cout << "XML file loading error! Error code: "
                    << doc.ErrorID()
                    << std::endl;
        }

        // TODO throw exception
//        if (failed) {
//            throw Exception;
//        }

        // make a node
        ns::AddressType address;
        double x = 0.0;
        double y = 0.0;

        XMLHandle docHandle( &doc );
        XMLElement* nodeElement = docHandle.FirstChild().FirstChildElement( "node" ).ToElement();
        if ( nodeElement )
        {
            address = nodeElement->Attribute("address");
        }

        nodeElement->QueryDoubleAttribute( "x", &x );
        nodeElement->QueryDoubleAttribute( "y", &y );

        ns.addNode(address);
    }

  private:

};

#endif //NS1_XMLREADER_H
