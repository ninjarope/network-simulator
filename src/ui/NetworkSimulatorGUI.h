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
     * Show current time.
     */
    void drawTime();
    
    /**
     * Show queues of links.
     */
    void drawQueues();
    
    /**
     * Show applications of all nodes.
     */
    void drawApplications();

    /**
     * Show distribution of traffic.
     */
    void drawTrafficDistribution();

    /**
     * Show distribution of queue lengths.
     */
    void drawQueueDistribution();

    /**
     * Stat display on / off.
     */
    void toggleStatVisibility();

    /**
     * Distribution display on / off.
     */
    void toggleDistributionVisibility();

    /**
     * Change between different distribution views.
     */
    void changeDistributionView();

    /**
     * Main function that is called from Network Simulator.
     * Encapsulates all UI subjects.
     */
    void update() override;
    
private:
    sf::RenderWindow* window;
    sf::Event event;
    sf::Font font;
    sf::Text text;
    sf::Color defaultNodeColor;
    sf::Color defaultDistColor;
    
    unsigned int fontSize;
    unsigned int nodeRadius;
    unsigned int width;
    unsigned int height;
    double transformX;
    double transformY;
    
    // Helper struct
    struct point {
        double x;
        double y;
    };
    std::map<ns::AddressType, point> visibleNodes;
    
    bool statsVisible;
    bool distributionVisible;
    enum {
        Traffic,
        Queue
    } distributionMode ;
};


#endif /* defined(__NetworkSimulator__NetworkSimulatorGUI__) */
