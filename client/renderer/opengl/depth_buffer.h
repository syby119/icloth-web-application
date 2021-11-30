#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "constant_interpret.h"

namespace gl {
class DepthBuffer {
public:
    DepthBuffer() {
        glDepthMask(interpret(_depthMask));
        glDepthFunc(interpret(_depthFunc));
        glClearDepth(_clearDepth);
    }

    ~DepthBuffer() = default;

    void setTest(bool enable) {
        if (enable) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void setMask(bool depthMask) {
        if (_depthMask != depthMask) {
            glDepthMask(depthMask ? GL_TRUE : GL_FALSE);
            _depthMask = depthMask;
        }
    }

    void setFunc(TestFunc depthFunc) {
        if (_depthFunc != depthFunc) {
            glDepthFunc(interpret(depthFunc));
            _depthFunc = depthFunc;
        }
    }

    void reset() {
        _depthMask = false;
        _depthFunc = TestFunc::LessEqual;
        _clearDepth = 1.0;
    }
private:
    // glDepthMask
    bool _depthMask = false;
    // glDepthFunc
    TestFunc _depthFunc = TestFunc::LessEqual;
    // glClearDepth
    double _clearDepth = 1.0;
};
}