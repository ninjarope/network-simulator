//
//  RandomNetworkGenerator.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 6.12.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__RandomNetworkGenerator__
#define __NetworkSimulator__RandomNetworkGenerator__

#include "../ns.h"
#include "NetworkSimulator.h"
#include "../node/ApplicationNode.h"
#include "../link/ParametricLink.h"
#include "../application/ApplicationFactory.h"

/** Class for generating random networks. */
class RandomNetworkGenerator {
public:
    explicit RandomNetworkGenerator(NetworkSimulator& ns, int nodeCount, int linkCount, int genCount);
    
    /** Generate random network based on given parameters. */
    void generate();
    
private:
    NetworkSimulator& ns;
    ApplicationFactory applicationFactory;
    const int nodeCount;
    const int linkCount;
    const int genCount;
    
};

#endif /* defined(__NetworkSimulator__RandomNetworkGenerator__) */
