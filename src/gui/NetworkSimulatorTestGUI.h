//
//  NetworkSimulatorTestGUI.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 14.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__NetworkSimulatorTestGUI__
#define __NetworkSimulator__NetworkSimulatorTestGUI__

#include "NetworkSimulatorGUI.h"

class NetworkSimulatorTestGUI : public NetworkSimulatorGUI {
public:
    NetworkSimulatorTestGUI() {}
    
    void update() override { std::cout << "GUI UPDATE..." << std::endl; }
    
private:
};

#endif /* defined(__NetworkSimulator__NetworkSimulatorTestGUI__) */
