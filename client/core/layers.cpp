#include <iostream>
#include "layers.h"

void Layers::set(int channel) noexcept {
    _mask = 1 << channel;
}

void Layers::enable(int channel) noexcept {
    _mask |= 1 << channel;
}

void Layers::enableAll() noexcept {
    _mask = 0xFFFFFFFF;
}

void Layers::toggle(int channel) noexcept {
    _mask ^= 1 << channel;
}

void Layers::disable(int channel) noexcept {
    _mask &= ~(1 << channel);
}

void Layers::disableAll() noexcept {
    _mask = 0;
}

bool Layers::isEnabled(int channel) const noexcept {
    return _mask & (1 << channel);
}

bool Layers::test(Layers layers) const noexcept {
    return _mask & layers._mask;
}

void Layers::printEnabledChannels() const {
    bool first = true;
    std::cout << "[";
    for (int channel = 0; channel < getMaxChannels(); ++channel) {
        if (isEnabled(channel)) {
            if (first) {
                std::cout << channel;
                first = false;
            } else {
                std::cout << ", " << channel;
            }
        }
    }
    std::cout << "]";
}