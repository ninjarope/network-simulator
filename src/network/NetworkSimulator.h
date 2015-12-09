//  NetworkSimulator.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__NetworkSimulator__
#define __NetworkSimulator__NetworkSimulator__

#include <memory>
#include <thread>

#include "../ns.h"
#include "Timer.h"
#include "Network.h"
#include "../ui/NetworkSimulatorUI.h"
#include "../application/ApplicationFactory.h"

/**
 * The controller
 */
class NetworkSimulator : public Network, public Timer {
public:
    NetworkSimulator();

    ~NetworkSimulator();
    
    /** Set UI. This object takes ownership of the pointer. */
    void setUI(NetworkSimulatorUI* ui);
    
    /**
     * Updates concurrently (in given max number of threads) the state of
     * all nodes and links.
     */
    void timerCallback() override;

    /** Starts timer and UI. */
    void start();

    /** Resets nodes, links and graph layout. */
    void reset();

    /** Terminate controller and UI. */
    void quit();

    /** Factory for application spawning. */
    ApplicationFactory* getApplicationFactory() const { return applicationFactory; }

    std::recursive_mutex mtx;
    
private:
    std::thread controllerThread;
    NetworkSimulatorUI* ui;
    ApplicationFactory* applicationFactory;
};
#endif /* defined(__NetworkSimulator__NetworkSimulator__) */
