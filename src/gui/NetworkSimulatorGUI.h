//
//  NetworkSimulatorGUI.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__NetworkSimulatorGUI__
#define __NetworkSimulator__NetworkSimulatorGUI__

#include "../network/NetworkSimulator.h"

/**
 * Abstract base class for all GUI implementations. 
 */
class NetworkSimulatorGUI {
public:
    NetworkSimulatorGUI();
    
    virtual ~NetworkSimulatorGUI();
    
    /** NetworkSimulator will call this. */
    void setNetworkSimulator(NetworkSimulator* ns);
    
    /** NetworkSimulator will call this in it's timer callbacks. */
    virtual void update() = 0;

protected:
    NetworkSimulator* networkSimulator;
};

#endif /* defined(__NetworkSimulator__NetworkSimulatorGUI__) */
