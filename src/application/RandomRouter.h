//
// Created by j on 11/17/15.
//

#ifndef NS1_RANDOMROUTER_H
#define NS1_RANDOMROUTER_H

#include "Application.h"
#include "../ns.h"

/**
 * Routes packets randomly
 */
class RandomRouter : public Application {
public:
    RandomRouter();

    void process(double timeDelta) override;

private:
    ns::Connections routingTable;
    ns::Connections connections;

};


#endif // NS1_RANDOMROUTER_H
