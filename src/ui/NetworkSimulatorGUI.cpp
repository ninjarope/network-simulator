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
#include <cmath>

NetworkSimulatorGUI::NetworkSimulatorGUI() {
    // Create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    width = videoMode.width;
    height = videoMode.height;
    window = new sf::RenderWindow(sf::VideoMode(width, height), "Network Simulator", sf::Style::Fullscreen, settings);
    
    // Load font and set font properties
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cout << "Font not found!" << std::endl;
    } else {
        std::cout << "Font loaded succesfully!" << std::endl;
    }

    fontSize = 14;
    text.setFont(font);
    text.setCharacterSize(fontSize); // in pixels
    text.setColor(sf::Color(255, 255, 255));
    text.setStyle(sf::Text::Regular);
    
    // Colors
    defaultNodeColor = sf::Color(128, 0, 196);
    defaultDistColor = sf::Color(64, 32, 128, 215);
    
    // Node properties
    nodeRadius = 20;
    
    // Other initializations
    statsVisible = false;
    distributionVisible = false;
    distributionMode = Traffic;
    transformX = width / 2.0;
    transformY = height / 2.0;
    
    // Set random seed
    srand((unsigned int) time(NULL));
}

NetworkSimulatorGUI::~NetworkSimulatorGUI() {
    window->close();
}

NetworkSimulatorUI *NetworkSimulatorGUI::createUI() { return new NetworkSimulatorGUI(); }


void NetworkSimulatorGUI::generateGraphLayout() {
    std::cout << "Generating layout..." << std::endl;
    visibleNodes.clear();
    
    double xMax = -DBL_MAX;
    double yMax = -DBL_MAX;
    double xSum = 0.0;
    double ySum = 0.0;
    int count = 0;
    
    for (auto &n : networkSimulator->getNodes()) {
        double x = n.second->getX();
        double y = n.second->getY();
        xSum += x;
        ySum += y;
        
        if (std::abs(x) > xMax) xMax = x;
        if (std::abs(y) > yMax) yMax = y;
        
        count++;
    }

    // Mid point
    double centerX = xSum / count;
    double centerY = ySum / count;
    
    // Apply scaling so that original aspect ratio is retained
    // and everything fits on the screen
    double xRatio = 0.5 * (width) / (xMax != 0.0 ? xMax : width);
    double yRatio = 0.5 * (height) / (yMax != 0.0 ? yMax : height);
    double scaleRatio;
    
    if (xRatio < yRatio) scaleRatio = xRatio;
    else scaleRatio = yRatio;
    
    for (auto &n : networkSimulator->getNodes()) {
        double x = scaleRatio * (n.second->getX() - centerX); // rand() % (width - nodeRadius * 2);
        double y = scaleRatio * (n.second->getY() - centerY); // rand() % (height - nodeRadius * 2);
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
        const int& x = n.second.x + transformX;
        const int& y = n.second.y + transformY;
        
        sf::CircleShape nodeShape(nodeRadius);
        
        // set color and transfrom
        nodeShape.setOutlineColor(defaultNodeColor);
        nodeShape.setOutlineThickness(1);
        nodeShape.setFillColor(sf::Color::Black);
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
        size_t queueFactor = std::min((int) l->getQueueLength(), 255);
        sf::Color sourceColor = sf::Color(128 + 0.5 * queueFactor,
                                        128 - 0.5 * queueFactor,
                                        128 - 0.5 * queueFactor,
                                        128 + 0.5 * queueFactor);
        
        sf::Color destinationColor = sf::Color(255,
                                               255,
                                               255,
                                               0);
        
        // Line between nodes
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(n1.x + nodeRadius + transformX, n1.y + nodeRadius + transformY), sourceColor),
            sf::Vertex(sf::Vector2f(n2.x + nodeRadius + transformX, n2.y + nodeRadius + transformY), destinationColor)
        };
        
        window->draw(line, 2, sf::Lines);
    }
}

void NetworkSimulatorGUI::drawTime() {
    std::stringstream ss;
    ss.precision(2);
    ss.setf(std::ios::fixed);
    ss
        << "CURRENT TIME: "
        << networkSimulator->getCurrentTime() / 1000.0
        << " s ";
    
    text.setString(ss.str());

    // Draw to rendering buffer
    text.setPosition(fontSize, fontSize);
    window->draw(text);
    
    ss = std::stringstream();
    
    ss
        << "[ESC] Exit   "
        << "[Enter] Restart   "
        << "[Space] Pause   "
        << "[G] Regenerate layout   "
        << "[S] Stats   "
        << "[D] Distribution   "
        << "[Q] Switch distribution mode";

    
    text.setString(ss.str());
    
    // Draw to rendering buffer
    text.setPosition(fontSize, height - fontSize);
    window->draw(text);


}

void NetworkSimulatorGUI::drawQueues() {
    // Construct the string to display
    std::stringstream ss;

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
    text.setPosition(fontSize, 2 * fontSize);
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

void NetworkSimulatorGUI::drawTrafficDistribution() {
    const auto& links = networkSimulator->getLinks();
    size_t n = links.size();
    double w = width / n;
    double xOffset;
  
    // Get max traffic
    long double totalTraffic = 1.0e-6;
    for (auto l : links) {
        size_t traffic = l->getTransmissionLog().size();
        totalTraffic += traffic;
    }
    
    // Draw relative bar graph showing distribution of traffic between the links
    for (auto i = 0; i < n; ++i) {
        size_t traffic = links[i]->getTransmissionLog().size();
        double h = height * traffic / totalTraffic;
        
        // Draw bar
        sf::RectangleShape rec(sf::Vector2f(w - 2, h));
        rec.setFillColor(defaultDistColor);
        rec.setPosition(i * w, height - h);
        window->draw(rec);
        
        // Generate label text
        std::stringstream ss;
        ss
            << links[i]->getSource()->getAddress()
            << "-"
            << links[i]->getDestination()->getAddress();
        
        // Draw label
        text.setString(ss.str());
        xOffset = (int) (w - text.getLocalBounds().width) / 2;
        text.setPosition(i * w + xOffset, height - fontSize * 4);
        window->draw(text);

        // Draw total packet count
        double percentage = traffic / totalTraffic * 100;
        ss = std::stringstream();
        ss.setf(std::ios::fixed);
        ss.precision(1);
        ss << (percentage > 1.0 ? percentage : 0) << " %";

        text.setString(ss.str());
        xOffset = (int) (w - text.getLocalBounds().width) / 2;
        text.setPosition(i * w + xOffset, height - fontSize * 3);
        window->draw(text);
    }

    // Draw global label
    text.setString("Total traffic distribution");
    xOffset = (int) (width - text.getLocalBounds().width) / 2;
    text.setPosition(xOffset, fontSize);
    window->draw(text);

}

void NetworkSimulatorGUI::drawQueueDistribution() {
    const auto& links = networkSimulator->getLinks();
    size_t n = links.size();
    double w = width / n;
    double xOffset;
    
    // Get max queueLength
    long double queueSum = 1.0e-6;
    for (auto l : links) {
        size_t queueLength = l->getQueueLength();
        queueSum += queueLength;
    }
    
    // Draw relative bar graph showing distribution of queueLength between the links
    for (auto i = 0; i < n; ++i) {
        size_t queueLength = links[i]->getQueueLength();
        double h = height * queueLength / queueSum;
        
        // Draw bar
        sf::RectangleShape rec(sf::Vector2f(w - 2, h));
        rec.setFillColor(sf::Color(128, 0, 0, 196));
        rec.setPosition(i * w, height - h);
        window->draw(rec);
        
        // Draw label
        std::stringstream ss;
        ss  << links[i]->getSource()->getAddress()
            << "-"
            << links[i]->getDestination()->getAddress();

        text.setString(ss.str());
        xOffset = (int) (w - text.getLocalBounds().width) / 2;
        text.setPosition(i * w + xOffset, height - fontSize * 4);
        window->draw(text);
        
        // Draw total packet count
        double percentage = queueLength / queueSum * 100;
        ss = std::stringstream();
        ss.setf(std::ios::fixed);
        ss.precision(1);
        ss << (percentage > 1.0 ? percentage : 0) << " %";
        
        text.setString(ss.str());
        xOffset = (int) (w - text.getLocalBounds().width) / 2;
        text.setPosition(i * w + xOffset, height - fontSize * 3);
        window->draw(text);
    }
    
    // Draw global label
    text.setString("Queue distribution");
    xOffset = (int) (width - text.getLocalBounds().width) / 2;
    text.setPosition(xOffset, fontSize);
    window->draw(text);
    
}


void NetworkSimulatorGUI::toggleStatVisibility() {
    if (statsVisible) statsVisible = false;
    else statsVisible = true;
}

void NetworkSimulatorGUI::toggleDistributionVisibility() {
    if (distributionVisible) distributionVisible = false;
    else distributionVisible = true;
}

void NetworkSimulatorGUI::changeDistributionView() {
    if (distributionMode == Traffic) distributionMode = Queue;
    else distributionMode = Traffic;
}

void NetworkSimulatorGUI::update() {
    // Event handling
    while (window->pollEvent(event))
    {
        // check the type of the event...
        switch (event.type)
        {
                // window closed
            case sf::Event::Closed:
                networkSimulator->quit();
                break;
                
                // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Return:
                        networkSimulator->start();
                        break;

                    case sf::Keyboard::Left:
                        transformX -= 10.0;
                        break;

                    case sf::Keyboard::Right:
                        transformX += 10.0;
                        break;

                    case sf::Keyboard::Up:
                        transformY -= 10.0;
                        break;
                        
                    case sf::Keyboard::Down:
                        transformY += 10.0;
                        break;

                    case sf::Keyboard::Space:
                        networkSimulator->toggleTimer();
                        break;
                        
                    case sf::Keyboard::D:
                        toggleDistributionVisibility();
                        break;

                    case sf::Keyboard::G:
                        generateGraphLayout();
                        break;

                    case sf::Keyboard::S:
                        toggleStatVisibility();
                        break;

                    case sf::Keyboard::Q:
                        changeDistributionView();
                        break;
                        
                    case sf::Keyboard::Escape:
                        networkSimulator->quit();
                        break;
                
                    default:
                        break;
                }
                break;
                
                // we don't process other types of events
            default:
                break;
        }
    }
    
    // Clear buffer
    window->clear();
    
    // Rendering subtasks
    drawLinks();
    drawNodes();
    
    if (distributionVisible) {
        switch (distributionMode) {
            case Traffic:
                drawTrafficDistribution();
                break;

            case Queue:
                drawQueueDistribution();
                
            default:
                break;
        }
    }

    if (statsVisible) {
        drawQueues();
        drawApplications();
    }
    
    drawTime();

    // Draw buffer to screen
    window->display();
}

