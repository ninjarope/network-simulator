//
//  NetworkSimulatorGUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 25.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulatorGUI.h"


NetworkSimulatorGUI::NetworkSimulatorGUI() {
    // Create window
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Network Simulator");
    
    // Load font and set properties
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cout << "Font not found!" << std::endl;
    } else {
        std::cout << "Font loaded succesfully!" << std::endl;
    }

    fontSize = 13;
    text.setFont(font);
    text.setCharacterSize(fontSize); // in pixels
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Regular);
    

}

NetworkSimulatorGUI::~NetworkSimulatorGUI() {
    delete window;
}

/**
 * Enables generic UI supertype and switching of its implementation layer.
 */
NetworkSimulatorUI *NetworkSimulatorGUI::createUI() { return new NetworkSimulatorGUI(); }

/**
 * Show traffic in a link. Search the link with parameters.
 *
 * @source          a node address
 * @destination     a node address
 */
void NetworkSimulatorGUI::displayTrafficLog(ns::AddressType source, ns::AddressType destination) {
    // print traffic logs
    const auto &l = networkSimulator->getLink(source, destination);
    std::cout
    << "Transmission log for link "
    << l->getSource()->getAddress()
    << l->getDestination()->getAddress()
    << " : "
    << std::endl;
    for (auto &logEntry : l->getTransmissionLog()) {
        std::cout
        << "["
        << logEntry.first
        << ", "
        << logEntry.second / 1000.0
        << "]"
        << std::endl;
    }
    
}

/**
 * Show queues of links
 */
void NetworkSimulatorGUI::drawQueues() {
    // Construct the string to display
    std::stringstream ss;
    
    ss << "CURRENT TIME: " << networkSimulator->getCurrentTime() / 1000.0 << " s" << std::endl;
    
    for (auto &l : networkSimulator->getLinks()) {
        ss  << "Queue length in front of link "
            << l->getSource()->getAddress()
            << l->getDestination()->getAddress()
            << " : "
            << l->getQueueLength()
            << std::endl;
    }
    
    // Convert stringstream to string
    text.setString(ss.str());
    
    // Draw to rendering buffer
    text.setPosition(0,0);
    window->draw(text);
}

/**
 * Show applications of all nodes
 */
void NetworkSimulatorGUI::drawApplications() {
    // Construct the string to display
    std::stringstream ss;
    
    ss << "Applications in the Network" << std::endl;
    
    for (auto &node : networkSimulator->getNodes()) {
        ss << "Node " << node.first << ": ";
        for (auto &app : node.second->getApplications()) {
            ss << "[" << app->getType() << "]";
        }
        ss << std::endl;
    }
    
    // Convert stringstream to string
    text.setString(ss.str());
    
    // Draw to rendering buffer
    text.setPosition(0, (networkSimulator->getLinks().size() + 3) * fontSize);
    window->draw(text);
}

/**
 * Main function that is called from Network Simulator.
 * Encapsulates all UI subjects.
 */
void NetworkSimulatorGUI::update() {
    // Clear buffer
    window->clear();
    
    // Subtasks
    drawQueues();
    drawApplications();
    
    // Draw buffer to screen
    window->display();
}

