//
//  Link.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__Link__
#define __NetworkSimulator__Link__

#include <map>
#include <atomic>
#include <mutex>

#include "../ns.h"
#include "../Notifiable.h"
#include "../node/Node.h"
#include "../packet/Packet.h"
#include "../node/Node.h"

/**
 * Abstract link base class. Links could destroy themselves if
 * they notice destination node has been deleted.
 */
class Link : public Notifiable {
public:
    /** Destroys all packets (packets will be lost) when link is removed. */
    virtual ~Link();
    
    /** Reset link. */
    virtual void reset() = 0;
    
    /** Add packet to queue waiting for transmission. Takes ownership of the packet. */
    void addPacket(Packet* p);
    
    /** Set source node. */
    bool setSource(Node* source);
    
    /** Set destination node. */
    bool setDestination(Node* destination);
    
    /** Get pointer to source node. */
    Node* getSource();
    
    /** Get pointer to destination node. */
    Node* getDestination();
    
    /** Set weight of the link. */
    void setWeight(double weight);
    
    /** Return weight of the link. */
    double getWeight();
    
    /** Set the transmission speed of the link that determines the interval at which new packets can be transmitted to the link. */
    void setTransmissionSpeed(double speed);
    
    /** Return current transmission speed. */
    double getTransmissionSpeed();
    
    /** Set the propagation delay, which is the time it takes for packet to travel across the link. */
    void setPropagationDelay(double speed);
    
    /** Return current propagation delay. */
    double getPropagationDelay();
    
    /** Return queue in front of the link. */
    const ns::Packets& getPacketsWaiting() const;
    
    /** Return length of queue in front of the link. */
    size_t getQueueLength();
    
    /** Return packets in transmission. */
    const std::map<Packet*, double>& getPacketsInTransmission() const;
    
    /** Return transmitted packets. */
    const ns::TransmissionLogType& getTransmissionLog() const;
    
    /**
     * Update state of the link. Links having speed and delay should consider time between calls
     * (currentTime).
     */
    virtual void run(double currentTime) = 0;
    
    std::recursive_mutex mtx;

protected:
    Link();
    
    Link(Node* source, Node* destination);
    
    Link(Node* source, Node* destination, double weight);
    
    Node* source;
    Node* destination;
    ns::Packets packetsWaiting;
    std::map<Packet*, double> packetsInTransmission; // {Packet*, [time to delivery]}
    ns::TransmissionLogType transmittedPackets; // {packetId, deliveryTime}
    double transmissionSpeed = 0.0;
    double propagationDelay = 0.0;
    double weight = 1.0;

};


#endif /* defined(__NetworkSimulator__Link__) */
