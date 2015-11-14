//
//  Application.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include "Application.h"
#include "../node/Node.h"

Application::Application() {}

Application::Application(Node* hostNode) { setHost(hostNode); }

Application::~Application() {}

void Application::setHost(Node* hostNode) { this->hostNode = hostNode; }

std::string Application::getType() const { return type; }
