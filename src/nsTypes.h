//
//  nsTypes.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__nsTypes__
#define __ns_sketch__nsTypes__

#include <string>
#include <queue>
#include <vector>
#include <map>
#include <list>

class Packet;
class Link;
class Node;
class NetworkSimulator;
class NetworkSimulatorUI;

namespace nsTypes {
    enum Notification {
        someNotificationType1,
        someNotificationType2
    };
    
    typedef std::string AddressType;
    typedef std::string PacketDataType;
    typedef std::list<Packet*> Packets;
    typedef std::vector<Link*> Connections;
    typedef std::map<AddressType, std::list<Node*>> PathsToDestinationAddress;
    typedef std::map<Node*, PathsToDestinationAddress> ShortestPaths;
    typedef std::list<Notification> Notifications;
}

#endif /* defined(__ns_sketch__nsTypes__) */
