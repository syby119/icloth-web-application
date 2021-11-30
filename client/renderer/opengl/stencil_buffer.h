#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "constant_interpret.h"

namespace gl {
class StencilBuffer {
public:
    StencilBuffer() {
        glStencilMask(_stencilMask);
        glStencilFunc(interpret(_stencilFunc), 
                      _stencilRef, _stencilFuncMask);
        glStencilOp(interpret(_stencilFail), 
                    interpret(_stencilZFail), 
                    interpret(_stencilZPass));
        glClearStencil(_clearStencil);
    }

    void setFunc(TestFunc stencilFunc, int stencilRef, int stencilFuncMask) {
        if (_stencilFunc     != stencilFunc ||
            _stencilRef      != stencilRef  ||
            _stencilFuncMask != stencilFuncMask) {
            glStencilFunc(interpret(stencilFunc), stencilRef, stencilFuncMask);
            _stencilFunc     = stencilFunc;
            _stencilRef      = stencilRef;
            _stencilFuncMask = stencilFuncMask;
        }
    }

    void setOp(StencilOp stencilFail, StencilOp stencilZFail, StencilOp stencilZPass) {
        if (_stencilFail  != stencilFail  ||
            _stencilZFail != stencilZFail ||
            _stencilZPass != stencilZPass) {
            glStencilOp(interpret(stencilFail), 
                        interpret(stencilZFail), 
                        interpret(stencilZPass));

            _stencilFail = stencilFail;
            _stencilZFail = stencilZFail;
            _stencilZPass = stencilZPass;
        }
    }

    void setClear(int clearStencil) {
        if (_clearStencil != clearStencil) {
            glClearStencil(clearStencil);
            _clearStencil = clearStencil;
        }
    }

    void reset() {
        int _stencilMask = 0xFF;
        TestFunc _stencilFunc = TestFunc::Always;
        int _stencilRef = 0;
        int _stencilFuncMask = 0xFF;
        StencilOp _stencilFail = StencilOp::Keep;
        StencilOp _stencilZFail = StencilOp::Keep;
        StencilOp _stencilZPass = StencilOp::Keep;
        int _clearStencil = 0;
    }
private:
    // glStencilMask
    int _stencilMask = 0xFF;
    // glStencilFunc
    TestFunc _stencilFunc = TestFunc::Always;
    int _stencilRef = 0;
    int _stencilFuncMask = 0xFF;
    // glStencilOp
    StencilOp _stencilFail = StencilOp::Keep;
    StencilOp _stencilZFail = StencilOp::Keep;
    StencilOp _stencilZPass = StencilOp::Keep;
    // glClearStencil
    int _clearStencil = 0;
};
}