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
#include "ApplicationNode.h"
#include "Link.h"


class Network {
public:
    Network();
    
    /* Return network nodes. */
    const std::vector<std::unique_ptr<ApplicationNode>>& getNodes() const;
    
    /* Return all links between nodes. */
    const std::vector<std::unique_ptr<Link>>& getLinks() const;
    
    /* Add new node to network. Network takes ownership of the node. */
    void addNode(ApplicationNode* n);
    
    /* Add new link between nodes. Network takes ownership of the link. */
    void addLink(Link* l);
    
private:
    std::vector<std::unique_ptr<ApplicationNode>> nodes;
    std::vector<std::unique_ptr<Link>> links;
};


#endif /* defined(__ns_sketch__Network__) */
