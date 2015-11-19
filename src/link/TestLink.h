//
//  TestLink.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__TestLink__
#define __NetworkSimulator__TestLink__

#include <iostream>
#include "Link.h"


/** Example implementation of link. */
class TestLink : public Link {
public:
    TestLink();
    
    /** Forward new packets to destination with no delay. */
    void run(double currentTime) override;
    
private:
};

#endif /* defined(__NetworkSimulator__TestLink__) */
