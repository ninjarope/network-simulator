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

#include "Application.h"
#include "Node.h"

//=============================================================
/* Node implementation that runs some application(s). */
class ApplicationNode : public Node {
public:
    ApplicationNode() {}
    
    ApplicationNode(nsTypes::AddressType address, Application* a) : Node(address) { addApplication(a); }
    
    void addApplication(Application* a) {
        a->setHost(this);
        applications.push_back(a);
    };
    
    /* Return types of applications. */
    std::string getType() const override {
        std::stringstream ss;
        for (auto& application : applications)
            ss << "[" << application->getType() << "]";
        return ss.str();
    }
    
    void run() override {
        // run all applications
        for (auto& application : applications)
            application->process();
    }
    
private:
    std::vector<Application*> applications;
};


#endif /* defined(__ns_sketch__ApplicationNode__) */
