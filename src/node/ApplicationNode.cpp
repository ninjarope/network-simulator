//
//  ApplicationNode.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "ApplicationNode.h"
#include "../ns.h"
#include "../application/Application.h"

ApplicationNode::ApplicationNode() {}

ApplicationNode::ApplicationNode(ns::AddressType address) : Node(address) {}

ApplicationNode::ApplicationNode(ns::AddressType address, Application* a) : Node(address) { addApplications(a);
}

ApplicationNode::ApplicationNode(ns::AddressType address,
                                 std::vector<Application*> applications) : Node(address){
    addApplications(applications);
}

void ApplicationNode::addApplications(Application* application) {
    if (application) {
        application->setHost(this);
        applications.push_back(std::unique_ptr<Application>(application));
    }
}

void ApplicationNode::addApplications(std::vector<Application*> applications) {
    for (auto a : applications) {
        addApplications(a);
    }
}

void ApplicationNode::setApplications(std::vector<Application*> applications) {
    this->applications.clear();
    addApplications(applications);
}

std::string ApplicationNode::getType() const {
    std::stringstream ss;
    for (auto& application : applications) {
        ss << "[" << application->getType() << "]";
    }
    return ss.str();
}

void ApplicationNode::run(double currentTime) {
    for (auto& application : applications)
        application->process(currentTime);
}
