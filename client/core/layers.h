#pragma once

class Layers {
public:
    Layers() = default;

    ~Layers() = default;

    void set(int channel) noexcept;

    void enable(int channel) noexcept;

    void enableAll() noexcept;

    void toggle(int channel) noexcept;

    void disable(int channel) noexcept;

    void disableAll() noexcept;

    bool isEnabled(int channel) const noexcept;

    bool test(Layers layers) const noexcept;

    void printEnabledChannels() const;

    constexpr int getMaxChannels() const noexcept { return 32; }
private:
    uint32_t _mask = 1;
};