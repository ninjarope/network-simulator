//
//  NetworkSimulatorGUI.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__NetworkSimulatorGUI__
#define __NetworkSimulator__NetworkSimulatorGUI__

#include <sstream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "NetworkSimulatorUI.h"
#include "../debug.h"

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
     * Render text boxes.
     */
    void drawTextBoxes();

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
     * Show routing between two nodes.
     */
    void drawRouting();

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
     * Sets focus on node if mouse cursor is on it.
     */
    void checkMouseOverNode(int x, int y);

    /**
     * Toggles select state of given node.     
     */
    void toggleSelect(ns::AddressType address);

    /**
     * Threaded callback to update GUI
     */
    void timerCallback() override;
    
    /** 
     * Return true if rendering window is created, false otherwise.
     */
    bool windowExists();
    
    void createTransmissionLogFile(Link* l);

    /**
     * Main function that is called from Network Simulator.
     * Encapsulates all UI subjects.
     */
    void update() override;
    
protected:
    sf::RenderWindow* window;
    sf::Event event;
    sf::Font font;
    sf::Text text;
    sf::Color defaultNodeColor;
    sf::Color defaultFillColor;
    sf::Color defaultDistColor;
    sf::Color selectedLinkColor;
    
    unsigned int fontSize;
    unsigned int nodeRadius;
    unsigned int windowWidth;
    unsigned int windowHeight;
    double transformX;
    double transformY;
    double zoom;
    bool statsVisible;
    bool distributionVisible;
    bool altDown = false;
    bool linkSelected;
    
    // Helper struct
    struct Point {
        double x;
        double y;
    };
    
    std::map<ns::AddressType, Point> visibleNodes;
    std::list<ns::AddressType> selectedNodes;
    ns::AddressType focusNode;
    Link* selectedLink;
    
    enum {
        Traffic,
        Queue
    } distributionMode;
    
    
};


#endif /* defined(__NetworkSimulator__NetworkSimulatorGUI__) */
