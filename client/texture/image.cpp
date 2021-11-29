#include <cstring> // std::memcpy

#include "image.h"

Image::Image(void* data, int width, int height, int channels, Type type)
    : _data(reinterpret_cast<char*>(data)), 
      _width(width), _height(height), _channels(channels), _type(type) {
}

Image::Image(const Image& image) {
    const size_t byteLength = image.getTotalBytes();
    _data = new char[byteLength];
    std::memcpy(_data, image._data, byteLength);
    _width = image._width;
    _height = image._height;
    _channels = image._channels;
    _type = image._type;
}

Image::Image(Image&& image) noexcept {
    _data = image._data;
    image._data = nullptr;
    _width = image._width;
    _height = image._height;
    _channels = image._channels;
    _type = image._type;
}

Image::~Image() {
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
}

Image& Image::operator=(const Image& image) {
    if (&image != this) {
        const size_t byteLength = image.getTotalBytes();

        if (getTotalBytes() != byteLength) {
            delete[] _data;
            _data = new char[byteLength];
        }

        std::memcpy(_data, image._data, byteLength);
        _width = image._width;
        _height = image._height;
        _channels = image._channels;
        _type = image._type;
    }

    return *this;
}

Image& Image::operator=(Image&& image) noexcept {
    if (&image != this) {
        _data = image._data;
        image._data = nullptr;
        _width = image._width;
        _height = image._height;
        _channels = image._channels;
        _type = image._type;
    }

    return *this;
}

size_t Image::getTotalBytes() const {
    size_t channelSize = 0;
    switch (_type) {
        case Type::Int8:
        case Type::Uint8:
            channelSize = 1;
            break;
        case Type::Int16:
        case Type::Uint16:
        case Type::HalfFloat:
            channelSize = 2;
            break;
        case Type::Float:
            channelSize = 4;
            break;
    }

    return channelSize  * _channels * _width * _height;
}