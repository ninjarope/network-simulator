//
//  ns.h
//  NetworkSimulator
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
    const int maxThreads = 64;
    const std::string logFilePath = "traffic_logs/";
    
    enum Notification {
        someNotificationType1,
        someNotificationType2
    };
    
    typedef std::string AddressType;
    typedef std::string PacketDataType;
    typedef std::vector<Packet*> Packets;
    typedef std::vector<Link*> Connections;
    typedef std::map<AddressType, std::list<Node*>> PathsToDestinationAddress;
    typedef std::string PacketIdType;
    typedef double TimePointType;
    typedef std::list<std::pair<PacketIdType, TimePointType>> TransmissionLogType;
    typedef std::multimap<AddressType, AddressType> LinkStorage;
    
    struct TotalWeight {
        AddressType nextHop;
        double totalWeight;
    };

    typedef std::map<ns::AddressType, TotalWeight> RoutingTable;
    // TODO This should be Minimal Cost Spanning Tree of links/nodes 
    typedef std::map<Node*, PathsToDestinationAddress> ShortestPaths;
    typedef std::list<Notification> Notifications;
}

#endif /* defined(__NetworkSimulator__ns__) */
