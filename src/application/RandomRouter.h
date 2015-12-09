//
//  RandomRouter.h
//  NetworkSimulator
//

#ifndef __ns1_randomrouter_h__
#define __ns1_randomrouter_h__

#include "Application.h"
#include "../ns.h"

/**
 * Routes packets randomly
 */
class RandomRouter : public Application {
public:
    RandomRouter();
    
    /** Set parameters of the application. */
    Application* setParameters(std::vector<std::string> parameters) override;
    /**
     * Empties the packet queue and routes them randomly
     */
    void process(double currentTime) override;

private:
    ns::Connections routingTable;
    ns::Connections connections;
};


#endif /** defined( __ns1_randomrouter_h__) */
