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


/* Example implementation of link. */
class TestLink : public Link {
public:
    TestLink();
    
    TestLink(Node* source, Node* destination);
    
    /* Forward new packets to destination with no delay. */
    void run(double timeProgress) override;
    
private:
};

#endif /* defined(__ns_sketch__TestLink__) */
