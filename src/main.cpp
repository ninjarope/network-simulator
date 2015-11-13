//
//  ns_classes.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include "NetworkSimulator.h"
#include "TestRouter.h"
#include "TestLink.h"

int main() {
    /* Simple test case. */
    
    // create some nodes
    std::vector<ApplicationNode*> nodes;
    nodes.push_back(new ApplicationNode("A", new TestRouter));
    nodes.push_back(new ApplicationNode("B", new TestRouter));
    nodes.push_back(new ApplicationNode("C", new TestRouter));

    // create some links between nodes
    std::vector<Link*> links;
    links.push_back(new TestLink(nodes[0], nodes[1]));
    links.push_back(new TestLink(nodes[1], nodes[2]));
  
    // create some packets
    std::vector<Packet> packets;
    packets.push_back(Packet("A", "B", "packet AB"));
    packets.push_back(Packet("A", "C", "packet AC"));
    packets.push_back(Packet("B", "C", "packet BC"));
    
    // assign packets to nodes
    nodes[0]->receivePacket (packets[0]);
    nodes[0]->receivePacket (packets[1]);
    nodes[1]->receivePacket (packets[2]);
    
    // add contents to simulator
    NetworkSimulator ns;
    ns.addNodes(nodes);
    ns.addLinks(links);
    
    // run few cycles
    int cycles = 3;
    for (int i = 1; i <= cycles; ++i) {
        std::cout << "CLOCK CYCLE " << i << std::endl;
        ns.timerCallback();
    }
}
