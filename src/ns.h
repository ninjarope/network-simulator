//
//  ns.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__ns__
#define __NetworkSimulator__ns__

#include <string>
#include <queue>
#include <vector>
#include <map>
#include <list>
#include <chrono>

class Packet;
class Link;
class Node;
class NetworkSimulator;
class NetworkSimulatorUI;

namespace ns {
    enum Notification {
        someNotificationType1,
        someNotificationType2
    };
    
    typedef std::string AddressType;
    typedef std::string PacketDataType;
    typedef std::list<Packet*> Packets;
    typedef std::vector<Link*> Connections;
    typedef std::map<AddressType, std::list<Node*>> PathsToDestinationAddress;
    typedef std::string PacketIdType;
    typedef double TimePointType;
    typedef std::list<std::pair<PacketIdType, TimePointType>> TransmissionLogType;
    
    /** \todo TODO This should be Minimal Cost Spanning Tree of links/nodes */
    typedef std::map<Node*, PathsToDestinationAddress> ShortestPaths;
    typedef std::list<Notification> Notifications;
}

#endif /* defined(__NetworkSimulator__ns__) */
