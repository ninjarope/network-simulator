//
// Created by j on 11/17/15.
//

#ifndef __ns1_randomrouter_h__
#define __ns1_randomrouter_h__

#include "Application.h"
#include "../nsTypes.h"

/**
 * Routes packets randomly
 */
class RandomRouter : public Application {
public:
    RandomRouter();

    void process(double timeDelta) override;

private:
    nsTypes::Connections routingTable;
    nsTypes::Connections connections;
    nsTypes::Packets packets;

};


#endif /** defined( __ns1_randomrouter_h__) */
