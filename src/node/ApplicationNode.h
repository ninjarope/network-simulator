//
//  ApplicationNode.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__ApplicationNode__
#define __ns_sketch__ApplicationNode__

#include <sstream>
#include <memory>

#include "Application.h"
#include "Node.h"

/* Node implementation that runs some application(s). */
class ApplicationNode : public Node {
public:
    ApplicationNode();
    
    /* Construct ApplicationNode with given address and initial application. */
    ApplicationNode(nsTypes::AddressType address, Application* a);
    
    /* Connect new application to host. Node takes ownership of the application. */
    void addApplication(Application* a);
    
    /* Return type names of applications that node is running. */
    std::string getType() const override;
    
    /* Run all connected applications. */
    void run(double timeProgress) override;
    
private:
    std::vector<std::unique_ptr<Application>> applications;
};


#endif /* defined(__ns_sketch__ApplicationNode__) */
