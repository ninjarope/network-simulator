//
//  NetworkSimulatorUI.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__NetworkSimulatorUI__
#define __NetworkSimulator__NetworkSimulatorUI__

#include "../ns.h"
#include "../network/NetworkSimulator.h"

/**
 * Abstract base class for all UI implementations. 
 */
class NetworkSimulatorUI {
public:
    NetworkSimulatorUI();
    
    virtual ~NetworkSimulatorUI();
    
    /** NetworkSimulator will call this. */
    void setNetworkSimulator(NetworkSimulator* ns);

    /** Display traffic log for given link in form of [packetID, delivery time] for each
     *  transmitted packet.
     */
    virtual void displayTrafficLog(ns::AddressType source, ns::AddressType destination) = 0;

    /** NetworkSimulator will call this in it's timer callbacks. */
    virtual void update() = 0;

protected:
    NetworkSimulator* networkSimulator;
};

#endif /* defined(__NetworkSimulator__NetworkSimulatorUI__) */
