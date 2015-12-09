//
//  ParametricLink.h
//  NetworkSimulator
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
    
    ParametricLink(double transmissionSpeed, double propagationDelay, double weight = 1.0);
    
    void reset() override;
    
    void run(double currentTime) override;
    
private:
    double previousTime;
    double packetToTransitTime;
    bool logging;
};

#endif /* defined(__NetworkSimulator__ParametricLink__) */
