//
//  RoutingGenerator.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 6.12.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__RoutingGenerator__
#define __NetworkSimulator__RoutingGenerator__

#include "Application.h"

class RoutingGenerator : public Application {
public:
    RoutingGenerator();
    
    /** Set parameters of the application. */
    Application* setParameters(std::vector<std::string> parameters) override {
        (void) parameters;
        return this;
    }
    /**
     * If host node is recipient of packet, receives (deletes) packet.
     */
    void process(double currentTime) override;
    
private:
    unsigned int rate;
    unsigned int count;
};


#endif /* defined(__NetworkSimulator__RoutingGenerator__) */
