//
// Created by j on 11/17/15.
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
    Application* setParameters(std::vector<std::string> parameters) override {
        (void) parameters;
        return this;
    }
    
    /** Update state of the router. */
    void process(double currentTime) override;

private:
    ns::Connections routingTable;
    ns::Connections connections;
};


#endif /** defined( __ns1_randomrouter_h__) */
