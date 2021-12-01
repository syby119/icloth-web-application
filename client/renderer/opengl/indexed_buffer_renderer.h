#pragma once

#include <glad/glad.h>

namespace gl {
class IndexedBufferRenderer {
public:
    void setMode(GLenum mode) {
        _mode = mode;
    }

    void render(int start, int count) {
        void* offset = reinterpret_cast<unsigned int*>(start * _bytePerIndex);
        glDrawElements(_mode, count, _indexType, offset);
    }

    void  renderInstances(int start, int count, int instanceCount) {
        void* offset = reinterpret_cast<unsigned int*>(start * _bytePerIndex);
        glDrawElementsInstanced(_mode, count, _indexType, offset, instanceCount);
    }
private:
    GLenum _mode = GL_TRIANGLES;
    GLenum _indexType = GL_UNSIGNED_INT;
    int _bytePerIndex = sizeof(unsigned int);
};
}