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

class NetworkSimulatorTestUI : public NetworkSimulatorUI {
public:
    NetworkSimulatorTestUI() {}
    
    void update() override { std::cout << "UI UPDATE..." << std::endl; }
    
private:
};

#endif /* defined(__NetworkSimulator__NetworkSimulatorTestUI__) */
