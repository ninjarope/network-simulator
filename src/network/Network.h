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
#include "../node/ApplicationNode.h"
#include "../link/Link.h"

/* Network class. This class should control all additions and removals
   of nodes and links. */
class Network {
public:
    Network();
    
    ~Network();
    
    /* Return all network nodes. */
    const std::map<nsTypes::AddressType, ApplicationNode*>& getNodes() const;
    
    /* Return all links between nodes. */
    const std::vector<Link*>& getLinks() const;
    
    /* Return single node. */
    ApplicationNode* operator[](nsTypes::AddressType address) const;

    ApplicationNode* getNode(nsTypes::AddressType address) const;
    
    /* Return single link. */
    const Link* getLink(nsTypes::AddressType source, nsTypes::AddressType destination) const;
    
    /* Add new node to network. Network takes ownership of the node. */
    bool addNode(nsTypes::AddressType address);
    
    /* Add new link between nodes. Network takes ownership of the link. */
    bool addLink(nsTypes::AddressType source, nsTypes::AddressType destination, Link* l);

    /* Remove node based on address. Returns true if successful. */
    bool removeNode(nsTypes::AddressType address);

    /* Remove link based on source and destination address. Returns true if successful. */
    bool removeLink(nsTypes::AddressType source, nsTypes::AddressType destination);
    
    /* Return number of nodes. */
    size_t getNodeCount();
    
    /* Return number of links: */
    size_t getLinkCount();

    /* Get addresses in current network. */
    const std::vector<nsTypes::AddressType>& getAddresses() const;
    
protected:
    std::vector<nsTypes::AddressType> addresses;
    std::map<nsTypes::AddressType, ApplicationNode*> nodes;
    std::vector<Link*> links;
};


#endif /* defined(__ns_sketch__Network__) */
