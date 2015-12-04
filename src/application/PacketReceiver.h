//
//  PacketReceiver.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__PacketReceiver__
#define __NetworkSimulator__PacketReceiver__

#include "../application/Application.h"

/**
 * Packet receiver application.
 *
 * Consumes packets from nodes packet queue
 */
class PacketReceiver : public Application {
public:
    PacketReceiver();
    
    /** Set parameters of the application. */
    Application* setParameters(std::vector<std::string> parameters) override {
        (void) parameters;
        return this;
    }
    /**
     * If host node is recipient of packet, receives (deletes) packet.
     */
    void process(double currentTime) override;
    
private:
    unsigned int rate;
    unsigned int count;
};

#endif /* defined(__NetworkSimulator__PacketReceiver__) */
