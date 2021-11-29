#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace gl {
class DepthBuffer {
public:
    void setTest(bool enable) {
        if (enable) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void setMask(bool depthMask) {
        if (currentDepthMask != depthMask) {
            glDepthMask(depthMask ? GL_TRUE : GL_FALSE);
            currentDepthMask = depthMask;
        }
    }

    void setFunc(TestFunc depthFunc) {
        if (currentDepthFunc != depthFunc) {
            glDepthFunc(interpret(depthFunc));
            currentDepthFunc = depthFunc;
        }
    }

    void reset() {
        currentDepthMask = false;
        currentDepthFunc = TestFunc::LessEqual;
        currentClearDepth = 1.0;
    }
private:
    bool currentDepthMask = false;
    TestFunc currentDepthFunc = TestFunc::LessEqual;
    double currentClearDepth = 1.0;
};
}