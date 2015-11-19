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

/** Link that makes use of transmission speed and propagation delay parameters. */
class ParametricLink : public Link {
public:
    ParametricLink();
    
    ParametricLink(double transmissionSpeed, double propagationDelay);
    
    /** Update state of the link. */
    void run(double currentTime) override;
    
private:
    double previousTime;
    double packetToTransitTime;
};

#endif /* defined(__NetworkSimulator__ParametricLink__) */
