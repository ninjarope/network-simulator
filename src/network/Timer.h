//
//  Timer.h
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#ifndef __ns_sketch__Timer__
#define __ns_sketch__Timer__

//=============================================================
class Timer {
public:
    Timer() {}
    
    virtual ~Timer() {}
    
    void setTimerIntervalSeconds(double seconds) {}
    
    double getTimerIntervalSeconds() { return interval; }
    
    void startTimer() {}
    
    void stopTimer() {}
    
    void setRunningTime(double seconds) {}
    
    virtual void timerCallback() = 0;
    
private:
    double interval;
    double runningTime;
};

#endif /* defined(__ns_sketch__Timer__) */
