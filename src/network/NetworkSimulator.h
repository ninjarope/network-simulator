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

//=============================================================
class NetworkSimulator : public Timer {
public:
    /* Some constructors, there could also be ones that initialze
     simulator from file etc... */
    NetworkSimulator() {}
    
    NetworkSimulator(const Network&) {}
    
    ~NetworkSimulator() {}
    
    void addNodes(std::vector<ApplicationNode*> nodes) {
        for (auto n : nodes) {
            network.addNode(n);
        }
    }
    
    void addLinks(std::vector<Link*> links) {
        for (auto l : links) {
            network.addLink(l);
        }
    }
    
    const Network& getNetworkState() const { return network; }
    
    /* Calls run() method (in multiple threads?) of all nodes and links. */
    void timerCallback() override {
        for (auto& node : network.getNodes()) node->run();
        for (auto& link : network.getLinks()) link->run();
    }
    
private:
    Network network;
};

#endif /* defined(__ns_sketch__NetworkSimulator__) */
