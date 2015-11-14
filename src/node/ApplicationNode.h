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

    /* Construct ApplicationNode with given address. */
    ApplicationNode(nsTypes::AddressType address);
    
    /* Construct ApplicationNode with given address and initial application. */
    ApplicationNode(nsTypes::AddressType address, Application* application);
    
    /* Construct ApplicationNode with given address and initial application. */
    ApplicationNode(nsTypes::AddressType address, std::vector<Application*> applications);
    
    /* Connect new applications to host. Node takes ownership of the application. */
    void addApplications(Application* application);
    
    void addApplications(std::vector<Application*> applications);

    /* Set applications (clears previous applications). */
    void setApplications(std::vector<Application*> applications);
    
    /* Return type names of applications that node is running. */
    std::string getType() const override;
    
    /* Run all connected applications. */
    void run(double timeProgress) override;
    
private:
    std::vector<std::unique_ptr<Application>> applications;
};


#endif /* defined(__ns_sketch__ApplicationNode__) */
