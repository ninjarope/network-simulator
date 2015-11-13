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
#include "ApplicationNode.h"
#include "Link.h"

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


#endif /* defined(__ns_sketch__Network__) */
