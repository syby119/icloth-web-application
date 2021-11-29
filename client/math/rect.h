#pragma once

struct Rect {
    int x, y, width, height;
};

inline bool operator==(const Rect& lhs, const Rect& rhs) noexcept {
    return lhs.x == rhs.x && 
           lhs.y == rhs.y && 
           lhs.width == rhs.width && 
           lhs.height == rhs.height;
}