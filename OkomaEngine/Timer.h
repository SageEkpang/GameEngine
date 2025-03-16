#ifndef TIMER_H
#define TIMER_H

#include "HeaderManager.h"
#include <chrono>

using namespace std::chrono;

class Timer
{
private:

    time_point<high_resolution_clock> m_StartClock;
    steady_clock::time_point m_StartTime;
    steady_clock::time_point m_LastFrame;

public:

    // CLASS FUNCTION(s)
    Timer();
    ~Timer();

    // BASE FUNCTION(s)
    float GetDeltaTime();
    void Tick();
    void Stop();

};

#endif
