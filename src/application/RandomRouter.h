//
// Created by j on 11/17/15.
//

#ifndef NS1_RANDOMROUTER_H
#define NS1_RANDOMROUTER_H

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


#endif NS1_RANDOMROUTER_H
