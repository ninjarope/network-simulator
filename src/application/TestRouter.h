//
//  TestRouter.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__TestRouter__
#define __ns_sketch__TestRouter__

#include "Application.h"
#include "../nsTypes.h"


/* Example implementation of application. Application implementation 
   could be given */
class TestRouter : public Application {
public:
    TestRouter();
    
    /* Simply forwards queued packets to the first link in host node connections 
       with no delay. */
    void process() override;
    
private:
    /* Router could generate routing table based on given shortest paths. ShortestPaths
       can be very large data structure in a large network, hence the pointer. 
       These variables are not actually used in this implementation. */
    nsTypes::ShortestPaths* shortestPaths;
    nsTypes::PathsToDestinationAddress routingTable;
};
#endif /* defined(__ns_sketch__TestRouter__) */
