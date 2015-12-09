//
//  Node.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__Node__
#define __NetworkSimulator__Node__

#include <map>
#include <atomic>
#include <mutex>

#include "../ns.h"
#include "../Notifiable.h"
#include "../packet/Packet.h"
#include "../link/Link.h"

/** Abstract base class for nodes. */
class Node : public Notifiable {
public:
    Node();

    /** Construct node and give it an address. */
    Node(ns::AddressType address);

    virtual ~Node();
    
    /** Receive new packet and assign it to queue. Takes ownership of the packet. */
    void receivePacket(Packet* p);

    /** Add new (outgoing) link to other node. Links will add themselves
       to connections by calling this function when they are created. */
    void addConnection(Link* link);

    /** Remove outgoing connection. Links can call this when deleting themselves. */
    void removeConnection(Link* link);

    /** Return connections (outgoing links). */
    ns::Connections& getConnections();

    /** Return packets currently in queue. */
    ns::Packets& getPackets();

    /** Return address of the node. */
    ns::AddressType getAddress();
    
    /** Return x coordinate. */
    double getX();

    /** Return y coordinate. */
    double getY();

    /** Derived classes must define their type and implement this. */
    virtual std::string getType() const = 0;

    /** Update routing table from given known complete shortest path. */
    void updateTable(std::vector<ns::AddressType> shortestPath);
    
    /** Update single routing table entry (total path cost to given destination). */
    void updateTable(ns::AddressType, ns::TotalWeight);
    
    /** Return modifiable routing table. */
    ns::RoutingTable& getRoutingTable();
    
    /** Get current lowest known path cost for given destination. */
    ns::TotalWeight getRoutingTableEntry(ns::AddressType address);
    
    /** Clear routing table of node. */
    void clearRoutingTable();
    
    /** Perform some actions when clock ticks. */
    virtual void run(double currentTime) = 0;
    
    std::recursive_mutex mtx;

protected:
    ns::Connections connections;
    ns::Packets packets;
    ns::AddressType address;

    // <destination, <nextHop, total path weight>>
    ns::RoutingTable routingTable;

    double x = 0;
    double y = 0;


};

#endif /** defined(__NetworkSimulator__Node__) */
