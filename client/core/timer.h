#pragma once

#include <chrono>

class Timer {
public:
    Timer() = default;

    ~Timer() = default;

    void start();

    void stop();

    void resume();

    float getElapsedTime() const;

    float getTotalTime() const;

    float getDeltaTime();

    bool Timer::paused() const;
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::duration<float>;

    TimePoint _startTimeStamp; // time point when calling start()
    TimePoint _lastTimeStamp;  // time point when calling start(), resume(), getDeltaTime()
    float _elapsedTime = 0.0f; // timer running time after calling start()
    bool _paused = true;       // timer status
};