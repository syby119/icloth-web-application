#pragma once

#include <glad/glad.h>

namespace gl {
class BufferRenderer {
public:
    void setMode(GLenum mode) {
        _mode = mode;
    }

    void render(int start, int count) {
        glDrawArrays(_mode, start, count);
    }

    void renderInstances(int start, int count, int instanceCount) {
        if (instanceCount != 0) {
            glDrawArraysInstanced(_mode, start, count, instanceCount);
        }
    }
private:
    GLenum _mode = GL_TRIANGLES;
};
}