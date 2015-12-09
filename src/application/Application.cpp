//
//  Application.cpp
//  NetworkSimulator
//

#include "Application.h"
#include "../node/Node.h"

Application::Application() {}

Application::Application(Node* hostNode) { setHost(hostNode); }

Application::~Application() {}

void Application::reset() {
    previousTime = 0.0;
    passedTime = 0.0;
}

void Application::setHost(Node* hostNode) { this->hostNode = hostNode; }

std::string Application::getType() const { return type; }
