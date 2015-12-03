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

enum ApplicationType {
    PACKET_RECEIVER,
    PACKET_GENERATOR,
    RANDOM_ROUTER,
    TEST_ROUTER
};

// http://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings
//std::map<ApplicationType, const char*> typeMap;
//map_init(typeMap)
//    (PACKET_RECEIVER, "PacketReceiver")
//    (PACKET_GENERATOR, "PacketGenerator")
//    (RANDOM_ROUTER, "RandomRouter")
//    (TEST_ROUTER, "TestRouter")
//;
//template<typename T> struct map_init_helper
//{
//    T& data;
//    map_init_helper(T& d) : data(d) {}
//    map_init_helper& operator() (typename T::key_type const& key, typename T::mapped_type const& value)
//    {
//        data[key] = value;
//        return *this;
//    }
//};
//
//template<typename T> map_init_helper<T> map_init(T& item)
//{
//    return map_init_helper<T>(item);
//}

class ApplicationFactory {
  public:
    ApplicationFactory(NetworkSimulator& ns_) : ns(ns_) { }
    ~ApplicationFactory() { }

    Application* create(ApplicationType t) {
        switch (t) {
            case PACKET_RECEIVER:
                return new PacketReceiver();
            case PACKET_GENERATOR:
                return new PacketGenerator(10);
            case RANDOM_ROUTER:
                return new RandomRouter();
            case TEST_ROUTER:
                return new TestRouter();

        }
    };
  private:
    NetworkSimulator& ns;
};

#endif //NS1_APPLICATIONFACTORY_H
