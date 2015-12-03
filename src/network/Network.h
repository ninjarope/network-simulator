//
//  Network.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//
#ifndef __NetworkSimulator__Network__
#define __NetworkSimulator__Network__
#include <vector>
#include <memory>
#include <iterator>
#include <iostream>
#include "../Notifiable.h"
#include "../node/ApplicationNode.h"
#include "../link/Link.h"
/**
 * Network class. This class should control all additions and removals
 * of nodes and links.
 */
class Network: public Notifiable {
  public:
    Network();
    ~Network();
    /** Return all network nodes. */
    const std::map<ns::AddressType, ApplicationNode*>& getNodes() const;
    /** Return all links between nodes. */
    const std::vector<Link*>& getLinks() const;
    /** Return single node. */
    ApplicationNode* operator[](ns::AddressType address) const;
    ApplicationNode* getNode(ns::AddressType address) const;
    /** Return single link. */
    const Link* getLink(ns::AddressType source, ns::AddressType destination) const;
    /** Add new node to network. Network takes ownership of the node. */
    bool addNode(ns::AddressType address);
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
  protected:
    std::vector <ns::AddressType> addresses;
    std::map<ns::AddressType, ApplicationNode*> nodes;
    std::vector<Link*> links;
    ns::LinkStorage allAvailableLinks;
};
#endif /* defined(__NetworkSimulator__Network__) */
