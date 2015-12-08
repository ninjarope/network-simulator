//
//  NetworkSimulatorTestUI.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__NetworkSimulatorTestUI__
#define __NetworkSimulator__NetworkSimulatorTestUI__

#include "NetworkSimulatorUI.h"

/**
 * Concrete UI class / TUI
 */
class NetworkSimulatorTestUI : public NetworkSimulatorUI {
public:
    NetworkSimulatorTestUI() {}
    
    static NetworkSimulatorUI* createUI();
    
    void generateGraphLayout() override {}
    
    void displayTrafficLog(ns::AddressType source, ns::AddressType destination) override;
    
    void drawQueues();
    
    void drawApplications();
    
    void hr();
    
    void update() override;

    void timerCallback() override { };
    
private:
};


#endif /* defined(__NetworkSimulator__NetworkSimulatorTestUI__) */
