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

Timer::Timer(int i, double s, int et) : interval(i), endTime(et), speed(s) { }

Timer::~Timer() {}

double Timer::getCurrentTime() { return currentTime; }

void Timer::setTimerInterval(double milliseconds) {}

double Timer::getTimerInterval() { return interval; }

void Timer::startTimer() {
    std::chrono::time_point<std::chrono::system_clock> callTime, returnTime;
    std::chrono::duration<double> callbackDuration;
    
    currentTime = 0.0;
    running = true;
    paused = false;

    while (running) {
        std::cerr << "OUTER LOOP " << paused << " " << currentTime << " " << endTime << std::endl;
        while(!paused && (endTime ? currentTime < endTime : true)) {
            callTime = std::chrono::system_clock::now();
            timerCallback();
            returnTime = std::chrono::system_clock::now();
            callbackDuration = returnTime - callTime;

            // delay if callback ran faster than the given interval
            if (callbackDuration < std::chrono::milliseconds(interval)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval) - callbackDuration);
            }

            currentTime += interval;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

void Timer::toggleTimer() {
    paused = !paused;
}

void Timer::stopTimer() { running = false; paused = true; }

void Timer::setRunningTime(double milliseconds) {}
