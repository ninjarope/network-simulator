//
//  ns_classes.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include "ns_classes.h"

int main() {
    NetworkSimulator ns;
    std::vector<ApplicationNode*> nodes;
    nodes.push_back(new ApplicationNode(new Router));
    nodes.front()->addApplication (new PacketGenerator);
    ns.addNodes(nodes);
    std::cout << ns.getNetworkState().getNodes().front()->getType() << std::endl;
}
