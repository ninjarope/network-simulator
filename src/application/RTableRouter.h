//
//  TestRouter.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__TestRouter__
#define __NetworkSimulator__TestRouter__

#include "Application.h"
#include "../ns.h"
#include <map>

/**
 * Example implementation of application. Application implementation
 * could be given
 */
class TestRouter : public Application {
public:
    TestRouter();

    /** Set parameters of the application. */
    Application* setParameters(std::vector<std::string> parameters) override {
        (void) parameters;
        return this;
    }

    /** Simply forwards queued packets to the first link in host node connections
       with no delay. */
    void process(double currentTime) override;

private:
    /** Router could generate routing table based on given shortest paths. ShortestPaths
       can be very large data structure in a large network, hence the pointer.
       These variables are not actually used in this implementation. */
    std::map<ns::AddressType,ns::AddressType> routingTable;
    //ns::PathsToDestinationAddress routingTable;
};
#endif /* defined(__NetworkSimulator__TestRouter__) */
