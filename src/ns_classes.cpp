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
    // create some nodes
    std::vector<ApplicationNode*> nodes;
    nodes.push_back(new ApplicationNode("A", new Router));
    nodes.push_back(new ApplicationNode("B", new Router));
    nodes.push_back(new ApplicationNode("C", new Router));

    // create some links
    std::vector<Link*> links;
    links.push_back(new LinkType1(nodes[0], nodes[1]));
    links.push_back(new LinkType1(nodes[1], nodes[2]));
  
    // create some packets and assign them to nodes
    std::vector<Packet> packets;
    packets.push_back(Packet("A", "B", "packet AB"));
    packets.push_back(Packet("A", "C", "packet AC"));
    packets.push_back(Packet("B", "C", "packet BC"));
    nodes[0]->receivePacket (packets[0]);
    nodes[0]->receivePacket (packets[1]);
    nodes[1]->receivePacket (packets[2]);
    
    // add contents to simulator
    NetworkSimulator ns;
    ns.addNodes(nodes);
    ns.addLinks(links);
    
    // run few cycles
    int cycles = 3;
    for (int i = 0; i < cycles; ++i) {
        std::cout << "CLOCK CYCLE " << i << std::endl;
        ns.timerCallback();
    }
}
