//
//  ApplicationNode.cpp
//  NetworkSimulator
//

#include "ApplicationNode.h"
#include "../ns.h"
#include "../application/Application.h"

ApplicationNode::ApplicationNode(double x, double y) {
    this->x = x;
    this->y = y;
}

ApplicationNode::ApplicationNode(double x, double y, ns::AddressType address) : Node(address) {
    this->x = x;
    this->y = y;
}

ApplicationNode::ApplicationNode(ns::AddressType address,
                                 std::vector<Application*> applications) : Node(address){
    addApplications(applications);
}

void ApplicationNode::reset() {
    // Enter critical section
    std::lock_guard<std::recursive_mutex> lock(mtx);
    
    packets.clear();
    for (auto& a : applications) a->reset();
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

const std::vector<std::unique_ptr<Application>> &ApplicationNode::getApplications() const {
    return applications;
}

std::string ApplicationNode::getType() const {
    std::stringstream ss;
    for (auto& application : applications) {
        ss << "[" << application->getType() << "]";
    }
    return ss.str();
}

void ApplicationNode::run(double currentTime) {
    for (auto& application : applications) {
        // Enter critical section
        application->process(currentTime);
    }
}
