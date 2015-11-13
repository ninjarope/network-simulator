//
//  ApplicationNode.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "ApplicationNode.h"

ApplicationNode::ApplicationNode() {}

ApplicationNode::ApplicationNode(nsTypes::AddressType address, Application* a) : Node(address) { addApplication(a);
}

void ApplicationNode::addApplication(Application* a) {
    a->setHost(this);
    applications.push_back(std::unique_ptr<Application>(a));
}

std::string ApplicationNode::getType() const {
    std::stringstream ss;
    for (auto& application : applications) {
        ss << "[" << application->getType() << "]";
    }
    return ss.str();
}

void ApplicationNode::run(double timeProgress) {
    for (auto& application : applications)
        application->process();
}
