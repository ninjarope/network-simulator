//
//  Timer.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Timer__
#define __ns_sketch__Timer__

/**
 * Cycles the clock for the network simulator state
 */
class Timer {
public:
    Timer();
    
    virtual ~Timer();
    
    /** Set timer interval in milliseconds. */
    void setTimerInterval(double milliseconds);
    
    /** Return timer interval. */
    double getTimerInterval();
    
    /** Reset and start timer. */
    void startTimer();
    
    /** Pause or resume timer (change current state). */
    void toggleTimer();
    
    /** Stop timer. */
    void stopTimer();
    
    /** Set maximum running time. */
    void setRunningTime(double seconds);
    
    /** Function will be called at set interval when timer is running. */
    virtual void timerCallback() = 0;
    
private:
    bool running;
    int intervalMs = 1000;
    double currentTime;
    double runningTime = 10000;
};

#endif /* defined(__ns_sketch__Timer__) */
