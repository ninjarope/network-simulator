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
    setSource(source);
    setDestination(destination);
}

Link::~Link() {
    // This could be also just notifying source node...
    source->removeConnection(this);
}

bool Link::setSource(Node* source) {
    if (source) {
        this->source = source;
        source->addConnection(this);
        return true;
    } else return false;
}

bool Link::setDestination(Node* destination) {
    if (destination) {
        this->destination = destination;
        return true;
    } else return false;

}

/* Add packet to queue waiting for transmission. */
void Link::addPacket(Packet p) { packetsWaiting.push_back(p); }

Node* Link::getSource() { return source; }

Node* Link::getDestination() { return destination; }
