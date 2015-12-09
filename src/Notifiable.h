//
//  Notifiable.h
//  NetworkSimulator
//

#ifndef __NetworkSimulator__Notifiable__
#define __NetworkSimulator__Notifiable__

/** Notification listener class. Can't be instantiated directly. */

#include <list>

#include "ns.h"

class Notifiable {
public:
    /** Add notification to pending notifications. */
    bool notify(ns::Notification) { return true; }

protected:
    Notifiable() {}
    
    ~Notifiable() {}
    
    /** Get pending notifications .*/
    ns::Notifications getNotifications() { return notifications; }
    
private:
    ns::Notifications notifications;

};

#endif /* defined(__NetworkSimulator__Notifiable__) */
