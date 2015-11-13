//
//  ns_classes.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__ns_classes__
#define __ns_sketch__ns_classes__

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <sstream>
#include <memory>
#include <utility>

// forward declarations
class Packet;
class Node;
class Link;
class Network;
class Application;
class Router;
class PacketGenerator;

//=============================================================

typedef std::string AddressType;
typedef std::map<AddressType, Link*> Connections;
typedef std::map<AddressType, std::list<Node*>> PathsToDestinationAddress;
typedef std::map<Node*, PathsToDestinationAddress> ShortestPaths;

//=============================================================
class Packet {
public:
    Packet() {}
    AddressType getSource() { return source; }
    AddressType getDestination() { return destination; }
    
private:
    AddressType source, destination;
};

//=============================================================
/* Abstract base class for nodes. */
class Node {
public:
    Node() {}
    virtual ~Node() {}
    void receivePacket(Packet);
    void addConnection(std::pair<AddressType, Link*>);
    Connections& getConnections() { return connections; }
    std::queue<Packet>& getPackets() { return packets; }
    AddressType getAddress() { return address; }
    virtual std::string getType() const = 0;
    virtual void run() = 0;
    
protected:
    Connections connections;
    std::queue<Packet> packets;
    AddressType address;
};

//=============================================================
/* Abstract link base class. */
class Link {
public:
    Link() {}
    Link(Node* begin, Node* end) {
        connection = {begin, end};
        begin->addConnection({end->getAddress(), this});
    }
    virtual ~Link() {}
    void addPacket(Packet) {}
    virtual void run() = 0;
    
protected:
    std::pair<Node*, Node*> connection;
    std::queue<Packet> packetsWaiting;
    std::vector<Packet> packetsInTransmission;
    double transmissionSpeed;
    double propagationDelay;
};

//=============================================================
/* Some implementation of link. */
class LinkType1 : public Link {
public:
    LinkType1() {}
    void run() override {}
    
private:
};

//=============================================================
/* Abstract node application base class. */
class Application {
public:
    Application() {}
    Application(Node* hostNode) {}
    void setHost(Node* node) { hostNode = node; }
    virtual ~Application() {}
    std::string getType() const { return type; }
    virtual void process() = 0;
    
protected:
    Node* hostNode;
    std::string type;
};

/* Routes and receives packets. */
class Router : public Application {
public:
    Router() { type = "Router"; }
    Router(ShortestPaths shortestPaths, Node* hostNode) {
        // set routing based on given paths
        // routing = shortestPaths.at(hostNode);
    }
    void process() override {
        // example implementation, forward packets to links
        // based on routing
        Packet p;
        AddressType packetDestination;
        std::queue<Packet>& packets = hostNode->getPackets();
        while (!packets.empty()) {
            p = packets.front();
            packetDestination = p.getDestination();
            routing.at(packetDestination).front()
                ->getConnections().at(packetDestination)
                ->addPacket(p);
            packets.pop();
        }
    }
    
private:
    /* Based on given shortest paths, associates next link to node in path
     for given packet destination address. */
    PathsToDestinationAddress routing;
};

/* Routes packets and generates new ones. */
class PacketGenerator : public Application {
public:
    PacketGenerator() { type = "PacketGenerator"; }
    PacketGenerator(ShortestPaths p, Node* hostNode) {}
    void process() override {}
    
private:
};

//=============================================================
class ApplicationNode : public Node {
public:
    ApplicationNode() {}
    ApplicationNode(Application* a) { addApplication(a); }
    void addApplication(Application* a) {
        a->setHost(static_cast<Node*> (this));
        applications.push_back(a);
    };
    std::string getType() const override {
        std::stringstream ss;
        for (auto& application : applications)
            ss << "[" << application->getType() << "]";
        ss << std::endl;
        
        return ss.str();
    }
    void run() override {
        // do something to the packets based on connections...
        for (auto& application : applications)
            application->process();
    }
    
private:
    std::vector<Application*> applications;
};

//=============================================================
class Timer {
public:
    Timer() {}
    virtual ~Timer() {}
    void setTimerIntervalSeconds(double seconds) {}
    double getTimerIntervalSeconds() { return interval; }
    void startTimer() {}
    void stopTimer() {}
    void setRunningTime(double seconds) {}
    virtual void timerCallback() = 0;
    
private:
    double interval;
    double runningTime;
};

//=============================================================
class Network {
public:
    Network() {}
    const std::vector<ApplicationNode*>& getNodes() const { return nodes; }
    const std::vector<Link*>& getLinks() const { return links; }
    void addNode(ApplicationNode* n) { nodes.push_back(n); }
    void addLink(Link* l) { links.push_back(l); }
    
private:
    std::vector<ApplicationNode*> nodes;
    std::vector<Link*> links;
};

//=============================================================
class NetworkSimulator : public Timer {
public:
    /* Some constructors, there could also be ones that initialze
     simulator from file etc... */
    NetworkSimulator() {}
    NetworkSimulator(const Network&) {}
    ~NetworkSimulator() {}
    void addNodes(std::vector<ApplicationNode*> nodes) {
        for (auto n : nodes) {
            network.addNode(n);
        }
    }
    const Network& getNetworkState() const { return network; } 
    
    /* Calls run() method (in multiple threads?) for all links 
     and nodes in network and optionally updates GUI. */
    void timerCallback() override {
        
    }
    
private:
    Network network;
    // GuiObject gui; ???
};


#endif /* defined(__ns_sketch__ns_classes__) */
