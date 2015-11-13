//
//  NetworkSimulator.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__NetworkSimulator__
#define __ns_sketch__NetworkSimulator__

#include "Timer.h"
#include "Network.h"


class NetworkSimulator : public Timer {
public:
    NetworkSimulator();
    
    NetworkSimulator(const Network&);
    
    ~NetworkSimulator();
    
    /* Add nodes to network. */
    void addNodes(std::vector<ApplicationNode*> nodes);
    
    /* Add links to network. */
    void addLinks(std::vector<Link*> links);
    
    /* Return current network state. */
    const Network& getNetworkState() const;
    
    /* Calls run() method (in multiple threads?) of all nodes and links. 
       In final implementation this function should be private. */
    void timerCallback() override;
    
private:
    Network network;
};

#endif /* defined(__ns_sketch__NetworkSimulator__) */
