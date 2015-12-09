//
//  RoutingGenerator.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__RoutingGenerator__
#define __NetworkSimulator__RoutingGenerator__

#include "Application.h"

/** Routing table generator application implementing distance-vector
  * routing protocol.
  */
class RoutingGenerator : public Application {
public:
    RoutingGenerator();
    
    /** Set parameters of the application. */
    Application* setParameters(std::vector<std::string> parameters) override {
        (void) parameters;
        return this;
    }
    
    /**
     * Frequently checks routing table of neighbor nodes and gradually
     * forms host node's routing table, based on lowest known total cost
     * of path to given destination node.
     */
    void process(double currentTime) override;
    
private:
    unsigned int rate;
    unsigned int count;
};

#endif /* defined(__NetworkSimulator__RoutingGenerator__) */
