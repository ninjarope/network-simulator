//
//  Timer.h
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __NetworkSimulator__Timer__
#define __NetworkSimulator__Timer__

#include <iostream>
#include "../ns.h"

/**
 * Cycles the clock for the network simulator state
 */
class Timer {
  public:

    Timer(int i = 10, double s = 1.0, int et = 10000);

    virtual ~Timer();

    /** Return current running time in milliseconds. */
    double getCurrentTime();

    /** Set timer's values */
    void setTimerValues(int, double, int);

    /** Set timer interval in milliseconds. */
    void setTimerInterval(int);
    void setTimerSlowdownrate(double);
    void setTimerEndTime(int);

    void slowdown() { slowdownrate /= 2.0; std::cout << "slowed down to " << slowdownrate << std::endl; }
    void fasten() { slowdownrate *= 2.0; std::cout << "fastened down to " << slowdownrate << std::endl; }

    /** Return timer interval. */
    double getTimerInterval();

    /** Reset and start timer. */
    void startTimer();

    /** Pause or resume timer (change current state). */
    void toggleTimer();

    /** Stop timer. */
    void stopTimer();
    
    /** Reset current time. */
    void resetTimer();

    /** Set maximum running time. */
    void setRunningTime(double seconds);

    /** Function will be called at set interval when timer is running. */
    virtual void timerCallback() = 0;

  protected:
    bool isRunning;
    bool isPaused;
    int interval;
    double currentTime;
    double slowdownrate;
    double endTime;
};

#endif /* defined(__NetworkSimulator__Timer__) */
