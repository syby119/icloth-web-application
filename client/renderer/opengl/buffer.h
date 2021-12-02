#pragma once

#include <cstdint>
#include <glad/glad.h>

namespace gl {
class Buffer {
public:
    Buffer(GLenum type, const void* data, GLenum dataType, 
           int itemSize, int itemCount, GLenum usage, uint32_t version)
        : _type(type), _dataType(dataType),
          _itemSize(itemSize), _itemCount(itemCount),
          _version(version) {
        glGenBuffers(1, &_handle);
        glBindBuffer(_type, _handle);
        glBufferData(_type, itemSize * itemCount, data, usage);
    }

    Buffer(const Buffer& rhs) = delete;

    Buffer(Buffer&& rhs) noexcept {
        _handle = rhs._handle;
        rhs._handle = 0;

        _type = rhs._type;
        _dataType = rhs._dataType;
        _itemSize = rhs._itemSize;
        _itemCount = rhs._itemCount;
        _version = rhs._version;
    }

    ~Buffer() {
        if (_handle) {
            glDeleteBuffers(1, &_handle);
            _handle = 0;
        }
    }

    Buffer& operator=(const Buffer& rhs) = delete;

    Buffer& operator=(Buffer&& rhs) noexcept = delete;

    void update(void* data, int offset = 0, int count = -1) {
        if (count == -1) {
            count = _itemSize * _itemCount;
        }

        glBindBuffer(_type, _handle);
        glBufferSubData(_type, offset * _itemSize, _itemSize * count, data);
    }

    bool getVersion() const {
        return _version;
    }

    void setVersion(uint32_t version) {
        _version = version;
    }
private:
    GLuint _handle = 0;      //< OpenGL buffer object
    GLenum _type;            //< buffer type
    GLenum _dataType = 0;    //< buffer data type
    int _itemSize = 0;       //< size of item
    int _itemCount = 0;      //< numbers of item
    uint32_t _version = 0;   //< version for update
};
}