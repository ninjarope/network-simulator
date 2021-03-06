//
//  NetworkSimulatorUI.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__NetworkSimulatorUI__
#define __NetworkSimulator__NetworkSimulatorUI__

#include "../ns.h"
#include "../network/NetworkSimulator.h"

/**
 * Abstract base class for all UI implementations. 
 */
class NetworkSimulatorUI : public Timer {
  public:
    virtual ~NetworkSimulatorUI();

    /** NetworkSimulator will call this. */
    void setNetworkSimulator(NetworkSimulator* ns);

    /**
     * Generate representation of the graph.
     */
    virtual void generateGraphLayout() = 0;

    /**
     * Display traffic log for given link in form of [packetID, delivery time] for each
     *  transmitted packet.
     */
    virtual void displayTrafficLog(ns::AddressType source, ns::AddressType destination) = 0;

    /** NetworkSimulator will call this in it's timer callbacks. */
    virtual void update() = 0;

  protected:
    NetworkSimulatorUI();

    NetworkSimulator* networkSimulator;

};

#endif /* defined(__NetworkSimulator__NetworkSimulatorUI__) */
