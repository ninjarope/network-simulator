//
//  Application.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Application__
#define __ns_sketch__Application__

#include <iostream>

#include "nsTypes.h"
#include "Packet.h"
#include "Node.h"
#include "Link.h"

//=============================================================
/* Abstract node application base class. */
class Application {
public:
    Application() {}
    
    Application(Node* hostNode) { setHost(hostNode); }
    
    /* Set host node that will run this application. */
    void setHost(Node* hostNode) { this->hostNode = hostNode; }
    
    virtual ~Application() {}
    
    std::string getType() const { return type; }
    
    /* Derived classes implement this - modifies node packets directly. */
    virtual void process() = 0;
    
protected:
    Node* hostNode;
    std::string type;
};

#endif /* defined(__ns_sketch__Application__) */
