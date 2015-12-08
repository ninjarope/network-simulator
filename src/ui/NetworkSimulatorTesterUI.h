//
//  NetworkSimulatorTesterUI.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__NetworkSimulatorTesterUI__
#define __NetworkSimulator__NetworkSimulatorTesterUI__

#include "../ns.h"
#include "../network/NetworkSimulator.h"
#include <thread>

/**
 * Abstract base class for all UI implementations. 
 */
class NetworkSimulatorTesterUI : public NetworkSimulatorUI {
  public:
    NetworkSimulatorTesterUI() {};
     ~NetworkSimulatorTesterUI() {};

    /**
 * Enables generic UI supertype and switching of its implementation layer.
 */
    static NetworkSimulatorTesterUI* createUI() { return new NetworkSimulatorTesterUI(); };

    /** NetworkSimulator will call this. */
    void setNetworkSimulator(NetworkSimulator* ns) { networkSimulator = ns; };

    /**
     * Generate representation of the graph.
     */
    void generateGraphLayout() override { };

    /**
     * Display traffic log for given link in form of [packetID, delivery time] for each
     *  transmitted packet.
     */
    void displayTrafficLog(ns::AddressType source, ns::AddressType destination) override { };

    void timerCallback() override {
#if DEBUG
        std::cerr << "UPDATE UI..." << std::endl;
#endif
        update();
    }
    /** NetworkSimulator will call this in it's timer callbacks. */
    void update() override { };


};

#endif /* defined(__NetworkSimulator__NetworkSimulatorTesterUI__) */