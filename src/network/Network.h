//
//  Network.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__Network__
#define __NetworkSimulator__Network__

#include <vector>
#include <memory>
#include <iostream>

#include "../Notifiable.h"
#include "../node/ApplicationNode.h"
#include "../link/Link.h"
#include "ShortestPath.h"

/**
 * Network class. This class should control all additions and removals
 * of nodes and links.
 */
class Network : public Notifiable {
  public:
    Network();
    ~Network();

    /** Return all network nodes. */
    std::map<ns::AddressType, ApplicationNode*>& getNodes();

    /** Return all links between nodes. */
    std::vector<Link*>& getLinks();

    /** Return single node. */
    ApplicationNode* operator[](ns::AddressType address);

    ApplicationNode* getNode(ns::AddressType address);

    /** Return single link. */
    Link* getLink(ns::AddressType source, ns::AddressType destination);

    /** Add new node to network. Network takes ownership of the node. */
    bool addNode(ns::AddressType address);
    bool addNode(double x, double y, ns::AddressType address);
    /** Add new link between nodes. Network takes ownership of the link. */
    bool addLink(ns::AddressType source, ns::AddressType destination, Link* l);

    /** Add new link between nodes that has a set weight property. Network takes ownership of the link. */
    bool addLink(ns::AddressType source, ns::AddressType destination, double weight, Link* l);

    /** Remove node based on address. Returns true if successful. */
    bool removeNode(ns::AddressType address);

    /** Remove link based on source and destination address. Returns true if successful. */
    bool removeLink(ns::AddressType source, ns::AddressType destination);

    /** Return number of nodes. */
    size_t getNodeCount();

    /** Return number of links: */
    size_t getLinkCount();

    /** check LinkStorage */
    void printLinks();

    /** Get addresses in current network. */
    const std::vector <ns::AddressType>& getAddresses() const;
    
    /** Updates the routing table of each node. */
    void updateRouting();

    /** Clears the routing table of each node. */
    void clearRouting();

    /** Clears the routing table of each node. */
    bool routingExists();

    /** Clears the routing table of each node. */
    const std::vector< std::vector<std::string>>& getPaths() const { return shortestPath.getShortestPaths(); }

  protected:
    std::vector <ns::AddressType> addresses;
    std::map<ns::AddressType, ApplicationNode*> nodes;
    std::vector<Link*> links;
    ns::LinkStorage allAvailableLinks;
    ShortestPath shortestPath;

};
#endif /* defined(__NetworkSimulator__Network__) */
