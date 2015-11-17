//
//  Timer.cpp
//  ns_sketch
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include <thread>

#include "Timer.h"

Timer::Timer() {
    interval = 1000;
    runningTime = 10000;
}

Timer::~Timer() {}

void Timer::setTimerInterval(double milliseconds) {}

double Timer::getTimerInterval() { return interval; }

void Timer::startTimer() {
    while (currentTime < runningTime) {
        std::cout << "CURRENT TIME: " << currentTime / 1000.0 << " s" << std::endl;
        timerCallback();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        currentTime += interval;
    }
    stopTimer();
}

void Timer::stopTimer() {}

void Timer::setRunningTime(double milliseconds) {}

