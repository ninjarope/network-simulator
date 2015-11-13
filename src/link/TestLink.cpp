//
//  TestLink.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "TestLink.h"

TestLink::TestLink() {}

TestLink::TestLink(Node* source, Node* destination) : Link(source, destination) {}

void TestLink::run(double timeProgress) {
    while (!packetsWaiting.empty()) {
        destination->receivePacket(packetsWaiting.front());
        std::cout
        << "Link " << this << " forwarded "
        << packetsWaiting.front().getData() << " to node "
        << destination->getAddress()
        << std::endl;
        packetsWaiting.pop();
    }
}
