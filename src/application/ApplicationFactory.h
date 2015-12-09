//
//  ApplicationFactory.h
//  NetworkSimulator
//

#ifndef NS1_APPLICATIONFACTORY_H
#define NS1_APPLICATIONFACTORY_H

#include "Application.h"
#include "PacketReceiver.h"
#include "PacketGenerator.h"
#include "RandomRouter.h"
#include "RTableRouter.h"
#include "RoutingGenerator.h"
#include "../network/NetworkSimulator.h"

/**
 * Acts as a middleman between all the applications and the components
 * that need to spawn them.
 */
class ApplicationFactory {
  public:
    /**
     * Encapsulates the different types of applications that
     * can be spawned with this factory
     */
    enum ApplicationType {
        PACKET_RECEIVER,
        PACKET_GENERATOR,
        RANDOM_ROUTER,
        RTABLE_ROUTER,
        ROUTING_GENERATOR
    };

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
            case RTABLE_ROUTER:
                return new RTableRouter();
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
