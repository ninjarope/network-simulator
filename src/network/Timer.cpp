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

Timer::Timer(int i, double s, int et) : interval(i), slowdownrate(s), endTime(et) { }

Timer::~Timer() {}

double Timer::getCurrentTime() { return currentTime; }

void Timer::setTimerInterval(int i) { interval = i; }
void Timer::setTimerSlowdownrate(double s) { slowdownrate = s; }
void Timer::setTimerEndTime(int et) { endTime = et; }

double Timer::getTimerInterval() { return interval; }

void Timer::startTimer() {
    std::chrono::time_point<std::chrono::system_clock> callTime, returnTime;
    std::chrono::duration<double> callbackDuration;
    
    currentTime = 0.0;
    isRunning = true;
    isPaused = false;

    while (isRunning) {
#if DEBUG
        std::cout << "OUTER LOOP " << isPaused << " " << currentTime << " " << endTime << std::endl;
#endif
        while(!isPaused && (endTime ? currentTime < endTime : true)) {
            // Calculate the call back functions elapsed time
            callTime = std::chrono::system_clock::now();
            timerCallback();
            returnTime = std::chrono::system_clock::now();
            callbackDuration = returnTime - callTime;

            // delay if callback ran faster than the given interval
            if (callbackDuration < std::chrono::milliseconds(interval)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval) - callbackDuration);
            }

            currentTime += interval / slowdownrate;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

void Timer::toggleTimer() {
    isPaused = !isPaused;
}

void Timer::stopTimer() { isRunning = false; isPaused = true; }

void Timer::setRunningTime(double milliseconds) {}
