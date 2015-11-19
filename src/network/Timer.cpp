//
//  Timer.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>

#include "Timer.h"

Timer::Timer() {
    interval = 10;
    endTime = 1000;
}

Timer::~Timer() {}

void Timer::setTimerInterval(double milliseconds) {}

double Timer::getTimerInterval() { return interval; }

void Timer::startTimer() {
    std::chrono::time_point<std::chrono::system_clock> callTime, returnTime;
    std::chrono::duration<double> callbackDuration;
    while (currentTime < endTime) {
        // debugging output
        std::cout << "CURRENT TIME: " << currentTime / 1000.0 << " s" << std::endl;
        
        callTime = std::chrono::system_clock::now();
        timerCallback();
        returnTime = std::chrono::system_clock::now();
        callbackDuration = returnTime - callTime;
        
        if (callbackDuration < std::chrono::milliseconds(interval)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval) - callbackDuration);
        }
        
        currentTime += interval;
    }
    stopTimer();
}

void Timer::stopTimer() {}

void Timer::setRunningTime(double milliseconds) {}

