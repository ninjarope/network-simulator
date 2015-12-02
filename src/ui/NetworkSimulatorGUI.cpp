//
//  NetworkSimulatorGUI.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 25.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "NetworkSimulatorGUI.h"
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

NetworkSimulatorGUI::NetworkSimulatorGUI() {
    // Create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    
    width = 800;
    height = 600;
    window = new sf::RenderWindow(sf::VideoMode(width, height), "Network Simulator", sf::Style::Default, settings);
    
    // Load font and set font properties
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cout << "Font not found!" << std::endl;
    } else {
        std::cout << "Font loaded succesfully!" << std::endl;
    }

    fontSize = 13;
    text.setFont(font);
    text.setCharacterSize(fontSize); // in pixels
    text.setColor(sf::Color(255, 255, 255, 128));
    text.setStyle(sf::Text::Regular);
    
    // Node properties
    nodeRadius = 20;
    
}

NetworkSimulatorGUI::~NetworkSimulatorGUI() {
    delete window;
}

NetworkSimulatorUI *NetworkSimulatorGUI::createUI() { return new NetworkSimulatorGUI(); }


void NetworkSimulatorGUI::generateGraphLayout() {
    srand((unsigned int) time(NULL));
    for (auto &n : networkSimulator->getNodes()) {
        unsigned int x = rand() % (width - nodeRadius * 2);
        unsigned int y = rand() % (height - nodeRadius * 2);
        visibleNodes.insert({n.first, {x, y}});
    }
}

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

void NetworkSimulatorGUI::drawNodes() {
    for (auto &n : visibleNodes) {
        const ns::AddressType& address = n.first;
        const int& x = n.second.x;
        const int& y = n.second.y;
        
        sf::CircleShape nodeShape(nodeRadius);
        
        // set color and transfrom
        nodeShape.setFillColor(sf::Color(150, 0, 0));
        nodeShape.setPosition(x, y);
        window->draw(nodeShape);
        
        // draw address on node
        text.setString(address);
        
        // Draw to rendering buffer
        text.setOrigin(fontSize / 2, fontSize / 2);
        text.setPosition(x + nodeRadius, y + nodeRadius);
        window->draw(text);
    }
}

void NetworkSimulatorGUI::drawLinks() {
    for (auto &l : networkSimulator->getLinks()) {
        // Start and end points (nodes)
        auto n1 = visibleNodes.at(l->getSource()->getAddress());
        auto n2 = visibleNodes.at(l->getDestination()->getAddress());
        
        // Color changes to red as queue grows
        sf::Color linkColor = sf::Color(std::min((int) l->getQueueLength(), 255),
                                        255 - std::min((int) l->getQueueLength(), 255),
                                        0);
        
        // Line between nodes
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(n1.x + nodeRadius, n1.y + nodeRadius), linkColor),
            sf::Vertex(sf::Vector2f(n2.x + nodeRadius, n2.y + nodeRadius), linkColor)
        };
        
        window->draw(line, 2, sf::Lines);
    }
}


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
    text.setPosition(fontSize, fontSize);
    window->draw(text);
}

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
    text.setPosition(fontSize, fontSize + (networkSimulator->getLinks().size() + 3) * fontSize);
    window->draw(text);
}

void NetworkSimulatorGUI::update() {
    // Clear buffer
    window->clear();
    
    // Subtasks
    drawLinks();
    drawNodes();
    drawQueues();
    drawApplications();
    
    // Draw buffer to screen
    window->display();
}

