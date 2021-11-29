#include "timer.h"

void Timer::start() {
    _startTimeStamp = Clock::now();
    _lastTimeStamp = _startTimeStamp;
    _elapsedTime = 0.0f;
    _paused = false;
}

void Timer::stop() {
    if (!_paused) {
        auto now = Clock::now();
        _elapsedTime += Duration(now - _lastTimeStamp).count();
        _paused = true;
    }
}

void Timer::resume() {
    if (_paused) {
        _lastTimeStamp = Clock::now();
        _paused = false;
    }
}

float Timer::getElapsedTime() const {
    float deltaTime = 0.0f;
    if (!_paused) {
        deltaTime = Duration(Clock::now() - _lastTimeStamp).count();
    }

    return _elapsedTime + deltaTime;
}

float Timer::getTotalTime() const {
    TimePoint now = Clock::now();
    return Duration(now - _startTimeStamp).count();
}

float Timer::getDeltaTime() {
    if (_paused) {
        return 0.0f;
    }

    TimePoint now = Clock::now();
    float deltaTime = Duration(now - _lastTimeStamp).count();
    _elapsedTime += deltaTime;

    _lastTimeStamp = now;

    return deltaTime;
}

bool Timer::paused() const {
    return _paused;
}
