//
//  Application.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__Application__
#define __NetworkSimulator__Application__

#include <iostream>

#include "../ns.h"
#include "../packet/Packet.h"
#include "../node/Node.h"
#include "../link/Link.h"


/**
 * Abstract node application base class.
 */
class Application: public Notifiable {
public:
    Application();
    
    /** Construct application and bind it to given host node. */
    Application(Node *hostNode);
    
    Application(Application &) = delete;
    Application &operator=(Application &) = delete;
    
    virtual ~Application();
    
    /** Reset time. */
    void reset();
    
    /** Set the host node that will be running this application. */
    void setHost(Node *hostNode);
    
    /** Return type identifier of the application. */
    std::string getType() const;
    
    /** Derived classes implement this - application has access to it's
     host via hostNode pointer. */
    virtual void process(double currentTime) = 0;
    
protected:
    Node *hostNode;
    std::string type;
    double previousTime;
    
};

#endif /* defined(__NetworkSimulator__Application__) */
