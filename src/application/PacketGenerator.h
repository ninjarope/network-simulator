//
//  PacketGenerator.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__PacketGenerator__
#define __NetworkSimulator__PacketGenerator__

#include "../application/Application.h"
#include "../network/Network.h"

/**
 * Packet generator application.
 * */
class PacketGenerator : public Application {
public:
    PacketGenerator();

    PacketGenerator(unsigned int rate);

    /** Construct packet generator that generates packets to given destinations at given rate. */
    PacketGenerator(unsigned int rate, std::vector<ns::AddressType> destinations);

    /** Set parameters of the application.
     *
     *  1   rate
     *  2-n possible destination addresses
     */
    Application* setParameters(std::vector<std::string> parameters) override;

    /**
     * Generates packets at given rate and adds them to host node
     * packet queue.
     */
    void process(double currentTime) override;

private:
    std::vector<ns::AddressType> destinations;
    unsigned int rate;
    unsigned int count;
};

#endif /* defined(__NetworkSimulator__PacketGenerator__) */
