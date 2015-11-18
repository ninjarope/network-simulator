//
//  Network.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Network__
#define __ns_sketch__Network__

#include <vector>
#include <memory>
#include "../Notifiable.h"
#include "../node/ApplicationNode.h"
#include "../link/Link.h"

/**
 * Network class. This class should control all additions and removals
 * of nodes and links.
 */
class Network : public Notifiable {
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

    /** Remove node based on address. Returns true if successful. */
    bool removeNode(ns::AddressType address);

    /** Remove link based on source and destination address. Returns true if successful. */
    bool removeLink(ns::AddressType source, ns::AddressType destination);
    
    /** Return number of nodes. */
    size_t getNodeCount();
    
    /** Return number of links: */
    size_t getLinkCount();

    /** Get addresses in current network. */
    const std::vector<ns::AddressType>& getAddresses() const;
    
protected:
    std::vector<ns::AddressType> addresses;
    std::map<ns::AddressType, ApplicationNode*> nodes;
    std::vector<Link*> links;
};


#endif /* defined(__ns_sketch__Network__) */
