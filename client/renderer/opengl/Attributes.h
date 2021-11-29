#pragma once

#include <glad/glad.h>
#include "core/buffer_attribute.hpp"

namespace gl {
class Attributes {
public:
    template<typename T>
    GLuint createBuffer(const BufferAttribute<T>& bufferAttribute, GLenum bufferType) {
        glCreateBuffers(1, &_buffer);
        glBindBuffer(bufferType, buffer);
        glBufferData(bufferType, bufferAttribute.getDataPtr(), bufferAttribute.getUsage());
        return buffer;
    }

    template<typename T>
    void updateBuffer(GLuint buffer, const BufferAttribute<T>& bufferAttribute, GLenum bufferType) {
        glBindBuffer(bufferType, buffer);
        // update the entire buffer
        glBufferSubData(bufferType, 0, bufferAttribute.getBufferSize(), bufferAttribute.getDataPtr());
    }

    void update(GLuint bufferObject) {
        _b
    }

    template<typename T>
    void update(const BufferAttribute<T>& bufferAttribute, GLenum bufferType) {
        buffer
    }
private:
    std::vector<GLuint> _bufferObjects;
};
}