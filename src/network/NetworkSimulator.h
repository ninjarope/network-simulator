//  NetworkSimulator.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//
#ifndef __NetworkSimulator__NetworkSimulator__
#define __NetworkSimulator__NetworkSimulator__
#include <memory>
#include <thread>
#include "../ns.h"
#include "Timer.h"
#include "Network.h"
#include "../ui/NetworkSimulatorUI.h"
#include "../application/ApplicationFactory.h"
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

    /** Starts timer and ui thread */
    void start();

    /** Resets nodes, links and graph layout */
    void reset();

    /** Terminate controller and UI. */
    void quit();

    /** Factory for application spawning */
    ApplicationFactory* getApplicationFactory() const { return applicationFactory; }

private:
    std::thread t;
    NetworkSimulatorUI* ui;
    ApplicationFactory* applicationFactory;
    std::thread nsThread;
};
#endif /* defined(__NetworkSimulator__NetworkSimulator__) */
