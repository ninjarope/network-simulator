//
//  NetworkSimulator.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__NetworkSimulator__
#define __ns_sketch__NetworkSimulator__

#include <memory>

#include "../nsTypes.h"
#include "Timer.h"
#include "Network.h"
#include "../ui/NetworkSimulatorUI.h"

/**
 * The controller
 */
class NetworkSimulator : public Network, public Timer {
public:
    NetworkSimulator();
    
    ~NetworkSimulator();
    
    void setUI(NetworkSimulatorUI* ui);
    
    /**
     * Calls run() method (in multiple threads?) of all nodes and links.
     * In final implementation this function should be private.
     */
    void timerCallback() override;
    
private:
    NetworkSimulatorUI* ui;
};

#endif /* defined(__ns_sketch__NetworkSimulator__) */
