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
#include <map>

#include "NetworkSimulatorUI.h"

/**
 * Concrete UI class / GUI
 */
class NetworkSimulatorGUI : public NetworkSimulatorUI {
public:
    NetworkSimulatorGUI();

    ~NetworkSimulatorGUI();

    /**
     * Enables generic UI supertype and switching of its implementation layer.
     */
    static NetworkSimulatorUI* createUI();
    
    /**
     * Generate layout based on network structure.
     */
    void generateGraphLayout() override;
    
    /**
     * Show traffic in a link. Search the link with parameters.
     *
     * @source          a node address
     * @destination     a node address
     */
    void displayTrafficLog(ns::AddressType source, ns::AddressType destination) override;

    /**
     * Render nodes.
     */
    void drawNodes();

    /**
     * Render links.
     */
    void drawLinks();

    /**
     * Show queues of links
     */
    void drawQueues();
    
    /**
     * Show applications of all nodes
     */
    void drawApplications();
   
    /**
     * Main function that is called from Network Simulator.
     * Encapsulates all UI subjects.
     */
    void update() override;
    
private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text text;
    unsigned int fontSize;
    unsigned int nodeRadius;
    unsigned int width;
    unsigned int height;
    
    // Helper struct
    struct point {
        unsigned int x;
        unsigned int y;
    };
    std::map<ns::AddressType, point> visibleNodes;
};


#endif /* defined(__NetworkSimulator__NetworkSimulatorGUI__) */
