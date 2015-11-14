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
#include "../gui/NetworkSimulatorGUI.h"

/**
 * The controller
 */
class NetworkSimulator : public Network, public Timer {
public:
    NetworkSimulator();
    
    ~NetworkSimulator();
    
    void setGUI(NetworkSimulatorGUI* gui);
    
    /**
     * Calls run() method (in multiple threads?) of all nodes and links.
     * In final implementation this function should be private.
     */
    void timerCallback() override;
    
private:
    NetworkSimulatorGUI* gui;
};

#endif /* defined(__ns_sketch__NetworkSimulator__) */
