//
//  Timer.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>

#include "Timer.h"

Timer::Timer() {
    interval = 20;
    endTime = 10000;
}

Timer::~Timer() {}

double Timer::getCurrentTime() { return currentTime; }

void Timer::setTimerInterval(double milliseconds) {}

double Timer::getTimerInterval() { return interval; }

void Timer::startTimer() {
    std::chrono::time_point<std::chrono::system_clock> callTime, returnTime;
    std::chrono::duration<double> callbackDuration;
    
    currentTime = 0.0;
    running = true;
    
    while (running) {
        // debugging output
        // std::cout << "CURRENT TIME: " << currentTime / 1000.0 << " s" << std::endl;

        callTime = std::chrono::system_clock::now();
        timerCallback();
        returnTime = std::chrono::system_clock::now();
        callbackDuration = returnTime - callTime;

        // delay if necessary
        if (callbackDuration < std::chrono::milliseconds(interval)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval) - callbackDuration);
        }

        if (currentTime < endTime and !paused) currentTime += interval;
    }
}

void Timer::toggleTimer() {
    if (paused) paused = false;
    else paused = true;
}

void Timer::stopTimer() { running = false; }

void Timer::setRunningTime(double milliseconds) {}
