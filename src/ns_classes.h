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
namespace NsTypes {
    typedef std::string AddressType;
    typedef std::string PacketDataType;
    typedef std::queue<Packet> PacketQueue;
    typedef std::vector<Link*> Connections;
    typedef std::map<AddressType, std::list<Node*>> PathsToDestinationAddress;
    typedef std::map<Node*, PathsToDestinationAddress> ShortestPaths;
}

//=============================================================
class Packet {
public:
    Packet() {}
    
    Packet(NsTypes::AddressType s, NsTypes::AddressType d, NsTypes::PacketDataType data)
        : source(s), destination(d), data(data) {}
    
    NsTypes::AddressType getSource() { return source; }
    
    NsTypes::AddressType getDestination() { return destination; }

    NsTypes::PacketDataType getData() { return data; }

private:
    NsTypes::AddressType source, destination;
    NsTypes::PacketDataType data;
};

//=============================================================
/* Abstract base class for nodes. */
class Node {
public:
    Node() {}
    
    Node(NsTypes::AddressType address) : address(address) {}
    
    virtual ~Node() {}
    
    void receivePacket(Packet p) { packets.push(p); }
    
    void addConnection(Link* link) { connections.push_back(link); }
    
    NsTypes::Connections& getConnections() { return connections; }
    
    NsTypes::PacketQueue& getPackets() { return packets; }
    
    NsTypes::AddressType getAddress() { return address; }
    
    virtual std::string getType() const = 0;
    
    virtual void run() = 0;
    
protected:
    NsTypes::Connections connections;
    NsTypes::PacketQueue packets;
    NsTypes::AddressType address;
};


//=============================================================
/* Abstract link base class. */
class Link {
public:
    Link() {}
    
    Link(Node* source, Node* destination) {
        this->source = source;
        this->destination = destination;
        source->addConnection(this);
    }
    
    virtual ~Link() {}
    
    /* Add packet to queue waiting for transmission. */
    void addPacket(Packet p) { packetsWaiting.push(p); }
    
    virtual void run() = 0;
    
protected:
    Node* source;
    Node* destination;
    NsTypes::PacketQueue packetsWaiting;
    std::vector<Packet> packetsInTransmission;
    double transmissionSpeed;
    double propagationDelay;
};

//=============================================================
/* Some test implementation of link, just straight forwarding of packets. */
class LinkType1 : public Link {
public:
    LinkType1() {}

    LinkType1(Node* source, Node* destination) : Link(source, destination) {}

    void run() override {
        while (!packetsWaiting.empty()) {
            destination->receivePacket(packetsWaiting.front());
            std::cout
                << "Link " << this << " forwarded "
                << packetsWaiting.front().getData() << " to node "
                << destination->getAddress()
                << std::endl;
            packetsWaiting.pop();
        }
    }
    
private:
};

//=============================================================
/* Abstract node application base class. */
class Application {
public:
    Application() {}
    
    Application(Node* hostNode) { setHost(hostNode); }
    
    /* Set host node that will run this application. */
    void setHost(Node* hostNode) { this->hostNode = hostNode; }
    
    virtual ~Application() {}
    
    std::string getType() const { return type; }
    
    /* Derived classes implement this - modifies node packets directly. */
    virtual void process() = 0;
    
protected:
    Node* hostNode;
    std::string type;
};

//=============================================================
/* Example router application class. */
class Router : public Application {
public:
    Router() { type = "Router"; }
    
    void process() override {
        // example with no routing, forward packets to "first" host node link, if any
        Packet p;
        NsTypes::AddressType packetDestination;
        NsTypes::PacketQueue& packets = hostNode->getPackets();
        while (!packets.empty()) {
            p = packets.front();
            packetDestination = p.getDestination();
            if (!hostNode->getConnections().empty()) {
                hostNode->getConnections().front()->addPacket(p);
                std::cout
                    << hostNode->getAddress() << " forwarded "
                    << p.getData() << " to link "
                    << hostNode->getConnections().front()
                    << std::endl;
            }
            packets.pop();
        }
    }
    
private:
    /* Routing table. */
    NsTypes::PathsToDestinationAddress routing;
};

/* Routes packets and generates new ones. */
class PacketGenerator : public Application {
public:
    PacketGenerator() { type = "PacketGenerator"; }
    
    void process() override {}
    
private:
};

//=============================================================
/* Node implementation that runs some application(s). */
class ApplicationNode : public Node {
public:
    ApplicationNode() {}
    
    ApplicationNode(NsTypes::AddressType address, Application* a) : Node(address) { addApplication(a); }
    
    void addApplication(Application* a) {
        a->setHost(this);
        applications.push_back(a);
    };
    
    /* Return types of applications. */
    std::string getType() const override {
        std::stringstream ss;
        for (auto& application : applications)
            ss << "[" << application->getType() << "]";
        return ss.str();
    }
    
    void run() override {
        // run all applications
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

    void addLinks(std::vector<Link*> links) {
        for (auto l : links) {
            network.addLink(l);
        }
    }

    const Network& getNetworkState() const { return network; }
    
    /* Calls run() method (in multiple threads?) of all nodes and links. */
    void timerCallback() override {
        for (auto& node : network.getNodes()) node->run();
        for (auto& link : network.getLinks()) link->run();
    }
    
private:
    Network network;
};


#endif /* defined(__ns_sketch__ns_classes__) */
