//
//  NetworkSimulatorGUI.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 25.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__NetworkSimulatorGUI__
#define __NetworkSimulator__NetworkSimulatorGUI__

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "NetworkSimulatorUI.h"

/**
 * Concrete UI class / GUI
 */
class NetworkSimulatorGUI : public NetworkSimulatorUI {
public:
    NetworkSimulatorGUI();

    ~NetworkSimulatorGUI();

    static NetworkSimulatorUI* createUI();
    
    void displayTrafficLog(ns::AddressType source, ns::AddressType destination) override;
    void drawQueues();
    void drawApplications();
    
    void update() override;
    
private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text text;
    unsigned int fontSize;
};


#endif /* defined(__NetworkSimulator__NetworkSimulatorGUI__) */
