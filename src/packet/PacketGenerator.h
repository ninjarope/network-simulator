//
//  PacketGenerator.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__PacketGenerator__
#define __ns_sketch__PacketGenerator__

#include "../application/Application.h"
#include "../network/Network.h"

/**
 * Packet generator application.
 * */
class PacketGenerator : public Application {
public:
    PacketGenerator();

    PacketGenerator(unsigned int rate);

    PacketGenerator(unsigned int rate, std::vector<nsTypes::AddressType> destinations);
    
    /** Generates packets at given rate and adds them to host node
       packet queue. */
    void process() override;
    
private:
    std::vector<nsTypes::AddressType> destinations;
    unsigned int rate;
    unsigned int count;
};

#endif /* defined(__ns_sketch__PacketGenerator__) */
