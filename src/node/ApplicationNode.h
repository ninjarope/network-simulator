//
//  ApplicationNode.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__ApplicationNode__
#define __NetworkSimulator__ApplicationNode__

#include <sstream>
#include <memory>

#include "../application/Application.h"
#include "Node.h"

/**
 * Node implementation that runs some application(s).
 */
class ApplicationNode : public Node {
public:
    ApplicationNode();

    /** Construct ApplicationNode with given address. */
    ApplicationNode(ns::AddressType address);
    
    /** Construct ApplicationNode with given address and initial application. */
    ApplicationNode(ns::AddressType address, Application* application);
    
    /** Construct ApplicationNode with given address and initial application. */
    ApplicationNode(ns::AddressType address, std::vector<Application*> applications);
    
    /** Connect new applications to host. Node takes ownership of the application. */
    void addApplications(Application* application);
    
    /** Connect multiple new applications to host. Node takes ownership of applications. */
    void addApplications(std::vector<Application*> applications);

    /** Set applications (clears previous applications). */
    void setApplications(std::vector<Application*> applications);
    
    /** Return type names of applications that node is running. */
    std::string getType() const override;
    
    /** Run all connected applications. */
    void run(double currentTime) override;
    
private:
    std::vector<std::unique_ptr<Application>> applications;
};


#endif /* defined(__NetworkSimulator__ApplicationNode__) */
