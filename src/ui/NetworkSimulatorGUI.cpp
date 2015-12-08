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
#include <cfloat>       /* DBL_MAX */
#include <algorithm>

NetworkSimulatorGUI::NetworkSimulatorGUI() : NetworkSimulatorUI() {
    // Create window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    windowWidth = videoMode.width;
    windowHeight = videoMode.height;
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Network Simulator", sf::Style::Fullscreen, settings);
    
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
    defaultFillColor = sf::Color(0, 0, 0, 160);
    defaultDistColor = sf::Color(64, 32, 128, 160);
    
    // Node properties
    nodeRadius = 20;
    
    // Other initializations
    statsVisible = false;
    distributionVisible = false;
    distributionMode = Traffic;
    transformX = windowWidth / 2.0;
    transformY = windowHeight / 2.0;
    zoom = 1.0;
    
    // Set random seed
    srand((unsigned int) time(NULL));
}

NetworkSimulatorGUI::~NetworkSimulatorGUI() {
    window->close();
}

NetworkSimulatorUI *NetworkSimulatorGUI::createUI() {
    return new NetworkSimulatorGUI;
}


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
    double xRatio = 0.5 * (windowWidth) / (xMax != 0.0 ? xMax : windowWidth);
    double yRatio = 0.5 * (windowHeight) / (yMax != 0.0 ? yMax : windowHeight);
    double scaleRatio;
    
    if (xRatio < yRatio) scaleRatio = xRatio;
    else scaleRatio = yRatio;
    
    for (auto &n : networkSimulator->getNodes()) {
        double x = scaleRatio * (n.second->getX() - centerX); // rand() % (windowWidth - nodeRadius * 2);
        double y = scaleRatio * (n.second->getY() - centerY); // rand() % (windowHeight - nodeRadius * 2);
        visibleNodes.insert({n.first, {x, y}});
    }
}

void NetworkSimulatorGUI::displayTrafficLog(ns::AddressType source, ns::AddressType destination) {
    // print traffic logs
    Link* l = networkSimulator->getLink(source, destination);
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
    sf::CircleShape nodeShape(nodeRadius);
    for (auto &n : visibleNodes) {
        // Hide others if two nodes selected
        if (selectedNodes.size() != 2
            || n.first == selectedNodes.front()
            || n.first == selectedNodes.back()) {
        const ns::AddressType& address = n.first;
        const int& x = n.second.x * zoom + transformX;
        const int& y = n.second.y * zoom + transformY;
            
        // set color and transfrom
        sf::Color outlineColor = defaultNodeColor;
        sf::Color fillColor = defaultFillColor;
        int thickness = 1;
        
        if (selectedNodes.front() == n.first || selectedNodes.back() == n.first) {
            fillColor = sf::Color(48, 0, 64, 255);
            outlineColor = sf::Color::White;
        }
        
        if (n.first == focusNode) {
            outlineColor = sf::Color::White;
        }
        
        nodeShape.setOutlineColor(outlineColor);
        nodeShape.setOutlineThickness(thickness);
        nodeShape.setFillColor(fillColor);
        nodeShape.setOrigin(nodeRadius, nodeRadius);
        nodeShape.setPosition(x, y);
        window->draw(nodeShape);
        
        // draw address on node
        text.setString(address);
        
        // Draw to rendering buffer
        //text.setOrigin(fontSize / 2, fontSize / 2);
        text.setPosition(x - text.getLocalBounds().width / 2, y - fontSize / 2);

        window->draw(text);
        }
    }
}

void NetworkSimulatorGUI::drawLinks() {
    for (auto &l : networkSimulator->getLinks()) {
        // Start and end points (nodes)
        try {
            auto n1 = visibleNodes.at(l->getSource()->getAddress());
            auto n2 = visibleNodes.at(l->getDestination()->getAddress());
            
            // Color changes
            double value = 0.0;
            size_t intensity;
            sf::Color sourceColor;
            
            if (distributionMode == Traffic) {
                value = (l->getPacketsInTransmission().empty() ? 0.0 : 255);
                intensity = std::min((int) value, 255);
                sourceColor = sf::Color(128 - 0.5 * intensity,
                                                  128 + 0.5 * intensity,
                                                  128 - 0.5 * intensity,
                                                  128 + 0.5 * intensity);
            }
            else if (distributionMode == Queue) {
                value = l->getQueueLength();
                intensity = std::min((int) value, 255);
                sourceColor = sf::Color(128 + 0.5 * intensity,
                                        128 - 0.5 * intensity,
                                        128 - 0.5 * intensity,
                                        128 + 0.5 * intensity);
            }
            
            sf::Color destinationColor = sf::Color(255,
                                                   255,
                                                   255,
                                                   0);
            
            // Line between nodes
            double x1 = n1.x * zoom + transformX;
            double y1 = n1.y * zoom + transformY;
            double x2 = n2.x * zoom + transformX;
            double y2 = n2.y * zoom + transformY;
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x1, y1), sourceColor),
                sf::Vertex(sf::Vector2f(x2, y2), destinationColor)
            };
            
            window->draw(line, 2, sf::Lines);
        } catch(std::out_of_range) {}
    }
}

void NetworkSimulatorGUI::drawTextBoxes() {
    // Pop-up boxes for selected nodes
    int i = 0;
    double margin = fontSize / 2;
    sf::Color boxColor = sf::Color(128, 128, 128);
    for (auto n : selectedNodes) {
        // Draw to rendering buffer
        text.setString(i++ == 0 ? "SOURCE" : "DESTINATION");
        sf::FloatRect textBounds = text.getLocalBounds();
        
        // Node center point
        int x = visibleNodes.at(n).x * zoom + transformX - textBounds.width / 2;
        int y = visibleNodes.at(n).y * zoom + transformY - textBounds.height / 2 - fontSize * 4;

        text.setPosition(x, y);
        
        // Box
        sf::RectangleShape rec(sf::Vector2f(textBounds.width + margin * 2,
                                            textBounds.height * 2.0 + margin * 2));
        
        rec.setFillColor(sf::Color(0, 0, 0, 128));
        rec.setOutlineColor(boxColor);
        rec.setOutlineThickness(1);
        rec.setPosition(x - margin, y - margin);
        
        // Pointing triangle
        sf::ConvexShape triangle(3);
        
        sf::FloatRect recBounds = rec.getLocalBounds();
        triangle.setPoint(0, sf::Vector2f(-5, 0));
        triangle.setPoint(1, sf::Vector2f(5, 0));
        triangle.setPoint(2, sf::Vector2f(0, 5));
        triangle.setPosition(x - margin + recBounds.width / 2, y - margin + recBounds.height);
    
        triangle.setFillColor(boxColor);
        triangle.setOutlineColor(boxColor);
        triangle.setOutlineThickness(1);
        
        window->draw(triangle);
        window->draw(rec);
        window->draw(text);
    }
}


void NetworkSimulatorGUI::drawTime() {
    long long totalTraffic = 0.0;
    for (auto l : networkSimulator->getLinks()) totalTraffic += l->getTransmissionLog().size();
    
    std::stringstream ss;
    ss.precision(2);
    ss.setf(std::ios::fixed);
    ss
        << "CURRENT TIME: "
        << networkSimulator->getCurrentTime() / 1000.0
        << " s   "
        << " ROUTING: "
        << (networkSimulator->routingExists() ? "shortest paths" : "random")
        << " TOTAL PACKETS TRANSMITTED: "
        << totalTraffic;
    
    
    text.setString(ss.str());

    // Draw to rendering buffer
    text.setPosition(fontSize, fontSize);
    window->draw(text);
    
    ss.str("");
    
    ss
        << "[ESC] Exit   "
        << "[Enter] Restart   "
        << "[Space] Pause   "
        << "[G] Switch routing   "
        << "[S] Stats   "
        << "[D] Distribution   "
        << "[M] Switch distribution mode   "
        << "[1, 2] Zoom   "
        << "[Arrow Keys] Move";

    
    text.setString(ss.str());
    
    // Draw to rendering buffer
    text.setPosition(fontSize, windowHeight - fontSize * 2);
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
    text.setPosition(fontSize, fontSize + (networkSimulator->getLinks().size() + 3) * (fontSize + 1));
    window->draw(text);
}

void NetworkSimulatorGUI::drawTrafficDistribution() {
    const auto& links = networkSimulator->getLinks();
    size_t n = links.size();
    double w = windowWidth / n;
    double xOffset;
    double maxTraffic = 0;
    sf::Color outlineColor = sf::Color::Black;
  
    // Get max traffic
    double totalTraffic = 1.0e-6;
    for (auto l : links) {
        size_t traffic = l->getTransmissionLog().size();
        totalTraffic += traffic;
        if (traffic > maxTraffic) maxTraffic = traffic;
    }
    
    // Draw relative bar graph showing distribution of traffic between the links
    for (auto i = 0; i < n; ++i) {
        size_t traffic = links[i]->getTransmissionLog().size();
        double h = (double) windowHeight * traffic / maxTraffic;
        
        // Draw bar
        sf::RectangleShape rec(sf::Vector2f(w - 2, h));
        rec.setFillColor(defaultDistColor);
        rec.setOutlineColor(outlineColor);
        rec.setOutlineThickness(0.5);
        rec.setPosition(i * w, windowHeight - h);
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
        text.setPosition(i * w + xOffset, windowHeight - fontSize * 5);
        if (n < 30) window->draw(text);

        // Draw total packet count
        double percentage = traffic / totalTraffic * 100;
        ss.str("");
        ss.setf(std::ios::fixed);
        ss.precision(1);
        ss << (percentage > 1.0 ? percentage : 0) << " %";

        text.setString(ss.str());
        xOffset = (int) (w - text.getLocalBounds().width) / 2;
        text.setPosition(i * w + xOffset, windowHeight - fontSize * 4);
        if (n < 30) window->draw(text);
    }

    // Draw global label
    text.setString("Total traffic distribution");
    xOffset = (int) (windowWidth - text.getLocalBounds().width) / 2;
    text.setPosition(xOffset, fontSize);
    window->draw(text);

}

void NetworkSimulatorGUI::drawQueueDistribution() {
    const auto& links = networkSimulator->getLinks();
    size_t n = links.size();
    double w = windowWidth / n;
    double xOffset;
    double maxQueue = 0;
    sf::Color outlineColor = sf::Color::Black;
    
    // Get max queueLength
    long double queueSum = 1.0e-6;
    for (auto l : links) {
        size_t queueLength = l->getQueueLength();
        queueSum += queueLength;
        if (queueLength > maxQueue) maxQueue = queueLength;
    }
    
    // Draw relative bar graph showing distribution of queueLength between the links
    for (auto i = 0; i < n; ++i) {
        size_t queueLength = links[i]->getQueueLength();
        double h = (double) windowHeight * queueLength / maxQueue;
        
        // Draw bar
        sf::RectangleShape rec(sf::Vector2f(w - 2, h));
        rec.setFillColor(sf::Color(128, 0, 96, 160));
        rec.setOutlineColor(outlineColor);
        rec.setOutlineThickness(0.5);
        rec.setPosition(i * w, windowHeight - h);
        window->draw(rec);
        
        // Draw label
        std::stringstream ss;
        ss  << links[i]->getSource()->getAddress()
            << "-"
            << links[i]->getDestination()->getAddress();

        xOffset = (int) (w - text.getLocalBounds().width) / 2;
        text.setString(ss.str());
        text.setPosition(i * w + xOffset, windowHeight - fontSize * 5);
        if (n < 30) window->draw(text);
        
        // Draw precentage
        double percentage = queueLength / queueSum * 100;
        ss.str("");
        ss.setf(std::ios::fixed);
        ss.precision(1);
        ss << (percentage > 1.0 ? percentage : 0) << " %";
        
        text.setString(ss.str());
        xOffset = (int) (w - text.getLocalBounds().width) / 2;
        text.setPosition(i * w + xOffset, windowHeight - fontSize * 4);
        if (n < 30) window->draw(text);
    }
    
    // Draw global label
    text.setString("Queue distribution");
    xOffset = (int) (windowWidth - text.getLocalBounds().width) / 2;
    text.setPosition(xOffset, fontSize);
    window->draw(text);
}

void NetworkSimulatorGUI::drawRouting() {
    // Check if there is source and destination selected
    if (!selectedNodes.empty()) {
        ns::AddressType source = selectedNodes.front();
        ns::AddressType dest = (selectedNodes.size() == 1 ? focusNode : selectedNodes.back());
    
        try {
            Node* n1 = networkSimulator->getNode(source);
            while (n1) {
                ns::AddressType next = n1->getRoutingTable().at(dest).nextHop;
                Node* n2 = networkSimulator->getNode(next);
                
                if (!n2) break;
                
                // Color changes to red as queue grows
                sf::Color pathColor = sf::Color(255, 255, 255);

                // Node coordinates
                double x1 = visibleNodes.at(n1->getAddress()).x * zoom + transformX;
                double y1 = visibleNodes.at(n1->getAddress()).y * zoom + transformY;
                double x2 = visibleNodes.at(n2->getAddress()).x * zoom + transformX;
                double y2 = visibleNodes.at(n2->getAddress()).y * zoom + transformY;
                
                // Line between nodes
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(x1, y1), pathColor),
                    sf::Vertex(sf::Vector2f(x2, y2), pathColor)
                };
                
                Link* l = networkSimulator->getLink(n1->getAddress(), n2->getAddress());
                std::stringstream ss;
                ss.precision(2);
                ss.setf(std::ios::fixed);
                if (l) ss << l->getWeight();
                
                sf::Text weight;
                weight.setFont(font);
                weight.setCharacterSize(14);
                weight.setColor(sf::Color::White);
                weight.setString(ss.str());
                weight.setOrigin((int) weight.getLocalBounds().width / 2, (int) weight.getLocalBounds().height / 2);
                weight.setPosition((int) (x2 + x1) / 2, (int) (y2 + y1) / 2);
                
                window->draw(line, 2, sf::Lines);
                if (dest == focusNode) {
                    sf::RectangleShape rec(sf::Vector2f(weight.getLocalBounds().width,
                                                        weight.getLocalBounds().height));
                    rec.setFillColor(sf::Color::Black);
                    rec.setOutlineColor(sf::Color::Black);
                    rec.setOutlineThickness(2);
                    rec.setPosition(weight.getGlobalBounds().left, weight.getGlobalBounds().top);
                    window->draw(rec);
                    window->draw(weight);
                }
                
                n1 = n2;
                if (next == dest) break;
            }
        } catch (std::out_of_range) {}
    }
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

void NetworkSimulatorGUI::checkMouseOverNode(int x, int y) {
    focusNode = "";
    
    for (auto n : visibleNodes) {
        int nx = n.second.x * zoom + transformX;
        int ny = n.second.y * zoom + transformY;
        if (std::sqrt(std::pow((double) nx - x, 2) + std::pow((double) ny - y, 2)) < nodeRadius) {
            focusNode = n.first;
        }
    }
}

void NetworkSimulatorGUI::toggleSelect(ns::AddressType address) {
    if (selectedNodes.empty()) selectedNodes.push_back(address);
    else if (selectedNodes.size() == 1) {
        for (auto it = selectedNodes.begin(); it != selectedNodes.end(); it++) {
            if (*it == address) {
                selectedNodes.erase(it);
                return;
            }
        }
        selectedNodes.push_back(address);
    } else if (selectedNodes.size() > 1) {
        for (auto it = selectedNodes.begin(); it != selectedNodes.end(); it++) {
            if (*it == address) {
                if (it == selectedNodes.begin()) selectedNodes.clear();
                else selectedNodes.pop_back();
                return;
            }
        }
        selectedNodes.pop_back();
        selectedNodes.push_back(address);
    }
}



void NetworkSimulatorGUI::update() {
    // Handle events
    std::cerr << "WINDOW ADDRESS: " << window << std::endl;
    //e->pollEvent();
    //std::queue<sf::Event> events = e->getEvents();
    //std::thread eventThread(&sf::Window::pollEvent, window, event);
    //eventThread.join();
    while (window->pollEvent(event))
    {
        //event = events.front();
        switch (event.type)
        {
            case sf::Event::Closed:
                networkSimulator->quit();
                break;
                
            case sf::Event::MouseMoved:
                checkMouseOverNode(event.mouseMove.x, event.mouseMove.y);
                break;
            
            case sf::Event::MouseButtonPressed:
                if (altDown) selectedNodes.clear();
                checkMouseOverNode(event.mouseButton.x, event.mouseButton.y);
                if (!focusNode.empty()) {
                    toggleSelect(focusNode);
                }
                break;
                
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Return:
                        networkSimulator->reset();
                        break;

                    case sf::Keyboard::Num1:
                        zoom /= 1.1;
                        break;

                    case sf::Keyboard::Num2:
                        zoom *= 1.1;
                        break;

                    case sf::Keyboard::Left:
                        transformX += 10.0 * zoom;
                        break;

                    case sf::Keyboard::Right:
                        transformX -= 10.0 * zoom;
                        break;

                    case sf::Keyboard::Up:
                        transformY += 10.0 * zoom;
                        break;
                        
                    case sf::Keyboard::Down:
                        transformY -= 10.0 * zoom;
                        break;

                    case sf::Keyboard::Space:
                        networkSimulator->toggleTimer();
                        break;
                        
                    case sf::Keyboard::D:
                        toggleDistributionVisibility();
                        break;

                    case sf::Keyboard::G:
                        if (!networkSimulator->routingExists()) networkSimulator->updateRouting();
                        else networkSimulator->clearRouting();
                        break;

                    case sf::Keyboard::S:
                        toggleStatVisibility();
                        break;

                    case sf::Keyboard::M:
                        changeDistributionView();
                        break;

                    case sf::Keyboard::Q:
                    case sf::Keyboard::Escape:
                        networkSimulator->quit();
                        break;

                    case sf::Keyboard::LAlt:
                        altDown = true;
                        break;
                
                    default:
                        break;
                }
                break;
            
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::LAlt:
                        altDown = false;
                        break;
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
    }
    // Clear buffer
    window->clear();
    
    // Rendering subtasks
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

    drawLinks();
    drawRouting();
    drawNodes();
    drawTextBoxes();

    if (statsVisible) {
        drawQueues();
        drawApplications();
    }
    
    drawTime();

    // Draw buffer to screen
    window->display();
}

