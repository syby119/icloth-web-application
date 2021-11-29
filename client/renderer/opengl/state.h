#pragma once

#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "constant_interpret.h"
#include "program.h"

namespace gl {
class ColorBuffer {
    glm::bvec4 currentColorMask = { false, false, false, false };
    glm::vec4 currentClearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
public:
    void setMask(glm::bvec4 colorMask) {
        if (currentColorMask != colorMask) {
            glColorMask(interpret(colorMask.r), 
                        interpret(colorMask.g),
                        interpret(colorMask.b),
                        interpret(colorMask.a));
            currentColorMask = colorMask;
        }
    }

    void setClear(glm::vec4 color, bool premultipiedAlpha = false) {
        if (premultipiedAlpha) {
            color.r *= color.a;
            color.g *= color.a;
            color.b *= color.a;
        }

        if (currentClearColor != color) {
            glClearColor(color.r, color.g, color.b, color.a);
            currentClearColor = color;
        }
    }

    void reset() {
        currentColorMask = glm::bvec4(false, false, false, false);
        currentClearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
};

class DepthBuffer {
    bool currentDepthMask = false;
    TestFunc currentDepthFunc = TestFunc::LessEqual;
    double currentClearDepth = 1.0;
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

};

class StencilBuffer {
    int currentStencilMask = 0xFF;
    TestFunc currentStencilFunc = TestFunc::Always;
    int currentStencilRef = 0;
    int currentStencilFuncMask = 0xFF;
    StencilOp currentStencilFail = StencilOp::Keep;
    StencilOp currentStencilZFail = StencilOp::Keep;
    StencilOp currentStencilZPass = StencilOp::Keep;
    int currentStencilClear = 0;
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
};

class State {
    ColorBuffer _colorBuffer;
    DepthBuffer _depthBuffer;
    StencilBuffer _stencilBuffer;
    Program* currentProgram = nullptr;

    struct Texture {
        GLenum type;
        GLuint textureObject;
    };

    unsigned int maxTextures = 0;

    GLenum currentTextureSlot;
    std::map<GLenum, Texture> currentBoundTextures;

    std::map<GLenum, GLuint> emptyTextures;


    struct Rect {
        int x, y;
        int width, height;
    };

    Rect currentScissor = { 0.0f, 0.0f, 0.0f, 0.0f };

    Rect currentViewport = { 0.0f, 0.0f, 0.0f, 0.0f };

    currentFlipSided = ;
    currentCullFace = ;
    float currentLineWidth = 0.0f;

  
    float currentPolygonOffsetFactor;
    float currentPolygonOffsetUnits;

public:
    State() {
        glGetParameter();

        emptyTextures();
    }

    void activeTexture(GLenum slot = GL_TEXTURE0 - 1) {
        if (slot == GL_TEXTURE0 - 1) {
            slot = GL_TEXTURE0 + maxTextures - 1;
        }

        if (currentTextureSlot != slot) {
            glActiveTexture(slot);
            currentTextureSlot = slot;
        }
    }

   /**
    * 绑定纹理
    * @param textureType  （gl.TEXTURE_2D、gl.TEXTURE_CUBE_MAP, gl.TEXTURE_3D, or gl.TEXTURE_2D_ARRAY.）
    * @param textureObject  纹理对象
    */
    void bindTexture(GLenum textureType, GLuint textureObject) {
        if (currentTextureSlot) {
            activeTexture();
        }

        auto it = currentBoundTextures.find(currentTextureSlot);

        if (it != currentBoundTextures.end()) {
            boundTexture();

        } else {
            glBindTexture(textureType, textureObject);
            it->second.type = textureType;
            it->second.textureObject = textureObject;
        }


    }

    void texImage2D() {
        glTexImage2D();
    }

    bool useProgram(const Program* program) {
        if (currentProgram != program) {
            program->use();
            currentProgram = program;
            return true;
        }

        return false;
    }

    void setLineWidth(float width) {
        if (width != currentLineWidth) {
            glLineWidth(width);
            currentLineWidth = width;
        }
    }

    void setPolygonOffset(bool enable, float factor, float units) {
        if (enable) {
            glEnable(GL_POLYGON_OFFSET_FILL);
            if (currentPolygonOffsetFactor != factor || 
                currentPolygonOffsetUnits != units) {
                glPolygonOffset(factor, units);
                currentPolygonOffsetFactor = factor;
                currentPolygonOffsetUnits = units;
            }
        } else {
            glDisable(GL_POLYGON_OFFSET_FILL);
        }
    }

    void setScissorTest(bool enable) {
        if (enable) {
            glEnable(GL_SCISSOR_TEST);
        } else {
            glDisable(GL_SCISSOR_TEST);
        }
    }

    void setScissor(int x, int y, int width, int height) {
        if (currentScissor.x != x || currentScissor.y != y || 
            currentScissor.width != width || currentScissor.height != height) {
            glScissor(x, y, width, height);
            currentScissor = { x, y, width, height };
        }
    }

    void setViewport(int x, int y, int width, int height) {
        if (currentViewport.x != x || currentViewport.y != y || 
            currentViewport.width != width || currentViewport.height != height) {
            glViewport(x, y, width, height);
            currentViewport = { x, y, width, height };
        }
    }

    void activeTexture();

    void bindTexture();

    void unbindTexture();

    void ttexSubImage2D();

    void texStorage2D();

    void reset() {
        currentTextureSlot = GL_TEXTURE0 - 1;
        currentBoundTextures.clear();

        currentProgram = nullptr;

        _colorBuffer.reset();
        _depthBuffer.reset();
        _stencilBuffer.reset();

        
    }
private:
    GLuint createEmptyTextures(GLenum textureType, void* data, int count) {
        GLuint textureObject = 0;
        glGenTextures(1, &textureObject);
        glBindTexture(textureType, textureObject);
        glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        for (int i = 0; i < count; ++i) {
            glTexImage2D(target);
        }
        return textureObject;
    }
};
}