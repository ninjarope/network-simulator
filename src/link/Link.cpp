//
//  Link.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Link.h"

Link::Link() {}

Link::Link(Node* source, Node* destination) {
    if (source && destination) {
        this->source = source;
        this->destination = destination;
        source->addConnection(this);
    }
}

Link::~Link() {}

/* Add packet to queue waiting for transmission. */
void Link::addPacket(Packet p) { packetsWaiting.push(p); }
