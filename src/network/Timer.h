//
//  Timer.h
//  NetworkSimulator
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
    
    /** Set timer interval scaling factor. */
    void setTimerSlowdownrate(double);
    
    /** Set end time (0 for infinity) */
    void setTimerEndTime(int);

    /** Slow down the timer. */
    void slowdown();
    
    /** Fasten the timer. */
    void fasten();

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
