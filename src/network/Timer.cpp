//
//  Timer.cpp
//  NetworkSimulator
//

#include <iostream>
#include <thread>
#include <chrono>

#include "Timer.h"

Timer::Timer(int i, double s, int et) : interval(i), slowdownrate(s), endTime(et) { }

Timer::~Timer() {}

double Timer::getCurrentTime() { return currentTime; }

void Timer::setTimerValues(int i, double s, int et) {
    setTimerInterval(i);
    setTimerSlowdownrate(s);
    setTimerEndTime(et);
}

void Timer::setTimerInterval(int i) { interval = i; }

void Timer::setTimerSlowdownrate(double s) { slowdownrate = s; }

void Timer::setTimerEndTime(int et) { endTime = et; }

void Timer::slowdown() { slowdownrate *= 2.0; }

void Timer::fasten() { slowdownrate /= 2.0; }

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
            int waitTime = (double) interval * slowdownrate;
            if (callbackDuration < std::chrono::milliseconds(waitTime)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(waitTime) - callbackDuration);
            }

            currentTime += interval;
        }

        int waitTime = (double) interval * slowdownrate;
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    }
}

void Timer::toggleTimer() {
    isPaused = !isPaused;
}

void Timer::stopTimer() {
    setTimerValues(1, 1.0, 1);
    isRunning = false;
    isPaused = true;
}

void Timer::resetTimer() { currentTime = 0.0; }

void Timer::setRunningTime(double milliseconds) {}
