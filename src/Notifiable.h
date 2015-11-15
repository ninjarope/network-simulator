//
//  Notifiable.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 15.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__Notifiable__
#define __NetworkSimulator__Notifiable__

/** Notification listener class. Can't be instantiated directly. */

#include <list>

#include "nsTypes.h"

class Notifiable {
public:
    /** Add notification to pending notifications. */
    bool notify(nsTypes::Notification) { return true; }

protected:
    Notifiable() {}
    
    ~Notifiable() {}
    
    /** Get pending notifications .*/
    nsTypes::Notifications getNotifications() { return notifications; }
    
private:
    nsTypes::Notifications notifications;

};

#endif /* defined(__NetworkSimulator__Notifiable__) */
