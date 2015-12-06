//
// Created by j on 12/3/15.
//

#ifndef NS1_APPLICATIONFACTORY_H
#define NS1_APPLICATIONFACTORY_H

#include "Application.h"
#include "PacketReceiver.h"
#include "PacketGenerator.h"
#include "RandomRouter.h"
#include "TestRouter.h"
#include "RoutingGenerator.h"
#include "../network/NetworkSimulator.h"


/**
 * Encapsulates the different types of applications that
 * can be spawned with this factory
 */
enum ApplicationType {
    PACKET_RECEIVER,
    PACKET_GENERATOR,
    RANDOM_ROUTER,
    TEST_ROUTER,
    ROUTING_GENERATOR
};

/**
 * Acts as a middleman between all the applications and the components
 * that need to spawn them.
 */
class ApplicationFactory {
  public:
    /**
     * Constructor takes network simulator reference to get
     * addresses for the creation of Packet Generator application
     */
    ApplicationFactory(NetworkSimulator& ns_) : ns(ns_) { }
    ~ApplicationFactory() { }

    /**
     * Creates the defined applications
     */
    Application* create(ApplicationType t) {
        switch (t) {
            case PACKET_RECEIVER:
                return new PacketReceiver();
            case PACKET_GENERATOR:
                return new PacketGenerator();
            case RANDOM_ROUTER:
                return new RandomRouter();
            case TEST_ROUTER:
                return new TestRouter();
            case ROUTING_GENERATOR:
                return new RoutingGenerator();
            default:
                ;
                // intentionally left as fall through
        }
        return nullptr;
    };
  private:
    NetworkSimulator& ns;
};

#endif //NS1_APPLICATIONFACTORY_H
