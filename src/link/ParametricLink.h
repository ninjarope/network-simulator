//
//  ParametricLink.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 18.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__ParametricLink__
#define __NetworkSimulator__ParametricLink__

#include <iostream>
#include <map>
#include "Link.h"

/** Example implementation of link. */
class ParametricLink : public Link {
public:
    ParametricLink();
    
    ParametricLink(double transmissionSpeed, double propagationDelay);
    
    /** Forward new packets to destination with no delay. */
    void run(double currentTime) override;
    
private:
    std::map<Packet*, double> timeToDelivery;
    double previousTime;
    double packetToTransitTime;
};

#endif /* defined(__NetworkSimulator__ParametricLink__) */
