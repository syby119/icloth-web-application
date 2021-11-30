#pragma once

template <typename T>
struct Rect {
    T x, y, width, height;
};

template <typename T>
inline bool operator==(const Rect<T>& lhs, const Rect<T>& rhs) noexcept {
    return lhs.x == rhs.x && 
           lhs.y == rhs.y && 
           lhs.width == rhs.width && 
           lhs.height == rhs.height;
}