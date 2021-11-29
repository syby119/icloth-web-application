#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace gl {
class StencilBuffer {
public:
    void setFunc(TestFunc stencilFunc, int stencilRef, int stencilFuncMask) {
        if (currentStencilFunc     != stencilFunc ||
            currentStencilRef      != stencilRef  ||
            currentStencilFuncMask != stencilFuncMask) {
            glStencilFunc(interpret(stencilFunc), stencilRef, stencilFuncMask);
            currentStencilFunc     = stencilFunc;
            currentStencilRef      = stencilRef;
            currentStencilFuncMask = stencilFuncMask;
        }
    }

    void setOp(StencilOp stencilFail, StencilOp stencilZFail, StencilOp stencilZPass) {
        if (currentStencilFail  != stencilFail  ||
            currentStencilZFail != stencilZFail ||
            currentStencilZPass != stencilZPass) {
            glStencilOp(interpret(stencilFail), 
                        interpret(stencilZFail), 
                        interpret(stencilZPass));

            currentStencilFail = stencilFail;
            currentStencilZFail = stencilZFail;
            currentStencilZPass = stencilZPass;
        }
    }

    void setClear(int stencilClear) {
        if (currentStencilClear != stencilClear) {
            glClearStencil(stencilClear);
            currentStencilClear = stencilClear;
        }
    }

    void reset() {
        int currentStencilMask = 0xFF;
        TestFunc currentStencilFunc = TestFunc::Always;
        int currentStencilRef = 0;
        int currentStencilFuncMask = 0xFF;
        StencilOp currentStencilFail = StencilOp::Keep;
        StencilOp currentStencilZFail = StencilOp::Keep;
        StencilOp currentStencilZPass = StencilOp::Keep;
        int currentStencilClear = 0;
    }
private:
    int currentStencilMask = 0xFF;
    TestFunc currentStencilFunc = TestFunc::Always;
    int currentStencilRef = 0;
    int currentStencilFuncMask = 0xFF;
    StencilOp currentStencilFail = StencilOp::Keep;
    StencilOp currentStencilZFail = StencilOp::Keep;
    StencilOp currentStencilZPass = StencilOp::Keep;
    int currentStencilClear = 0;
};
}