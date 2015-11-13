//
//  TestLink.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__TestLink__
#define __ns_sketch__TestLink__

#include <iostream>
#include "Link.h"

//=============================================================
/* Some test implementation of link, just straight forwarding of packets. */
class TestLink : public Link {
public:
    TestLink() {}
    
    TestLink(Node* source, Node* destination) : Link(source, destination) {}
    
    void run() override {
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
    
private:
};

#endif /* defined(__ns_sketch__TestLink__) */
