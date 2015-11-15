//
//  NetworkComponent.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 15.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__NetworkComponent__
#define __NetworkSimulator__NetworkComponent__

/** Base class for all network components. Can't be instantiated directly. */

#include <list>

#include "../nsTypes.h"

class NetworkComponent {
public:
    /** Add notification to pending notifications. */
    bool notify(nsTypes::Notifications) { return true; }

protected:
    NetworkComponent() {}
    
    ~NetworkComponent() {}
    
    /** Get pending notifications .*/
    nsTypes::Notifications getNotifications() { return notifications; }
    
private:
    nsTypes::Notifications notifications;

};

#endif /* defined(__NetworkSimulator__NetworkComponent__) */
