#pragma once

#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../math/rect.h"
#include "../material/material.h"

#include "constant_interpret.h"
#include "color_buffer.h"
#include "depth_buffer.h"
#include "stencil_buffer.h"

namespace gl {
class State {
public:
    // to do
    State();

    void activeTexture(GLenum slot = 0);

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

    // to do
    void texImage2D() {
        glTexImage2D();
    }

    bool useProgram() {
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

    void setPolygonOffset(bool enable, float factor = 0.0f, float units = 0.0f) {
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

    void setFlipSided(bool flag) {
        if (currentFlipSided != flag) {
            if (flag) {
                gl_FrontFace(GL_CW);
            } else {
                gl_FrontFace(GL_CCW);
            }

            currentFlipSided = flag;
        }
    }
    
    void setCullFace() {
        assert(0);
    }

    // to do
    void setMaterial(const Material& material, FrontFace facing) {
        if (material.renderFace == RenderFace::Double) {
            glDisable( GL_CULL_FACE );
        } else {
            glEnable(GL_CULL_FACE);
        }
 
        var flipSided = ( material.side === BackSide );
        if ( frontFaceCW ) flipSided = ! flipSided;
 
        setFlipSided( flipSided );
 
      ( material.blending === NormalBlending && material.transparent === false )
         ? setBlending( NoBlending )
         : setBlending( material.blending, material.blendEquation, material.blendSrc, material.blendDst, material.blendEquationAlpha, material.blendSrcAlpha, material.blendDstAlpha, material.premultipliedAlpha );
 
      depthBuffer.setFunc( material.depthFunc );
      depthBuffer.setTest( material.depthTest );
      depthBuffer.setMask( material.depthWrite );
      colorBuffer.setMask( material.colorWrite );
 
      setPolygonOffset( material.polygonOffset, material.polygonOffsetFactor, material.polygonOffsetUnits );
 
    }

    // to do
    void activeTexture();

    // to do
    void bindTexture();

    // to do
    void unbindTexture();

    // to do
    void ttexSubImage2D();

    // to do
    void texStorage2D();

    // to do
    void reset() {
        currentTextureSlot = GL_TEXTURE0 - 1;
        currentBoundTextures.clear();

        currentProgram = nullptr;

        colorBuffer.reset();
        depthBuffer.reset();
        stencilBuffer.reset();
    }
public:
    ColorBuffer colorBuffer;
    DepthBuffer depthBuffer;
    StencilBuffer stencilBuffer;
private: 
    GLuint currentProgram = 0;

    BlendMode blendMode = BlendMode::Add;
    bool blendAlpha = false;
    BlendMode blendAlphaMode = BlendMode::Add;
    BlendFactor currentBlendSrcFactor = BlendFactor::SrcAlpha;
    BlendFactor blendDstFactor = BlendFactor::OneMinusSrcAlpha;
    bool blendSeparate = false;
    BlendFactor blendSrcAlphaFactor = BlendFactor::Zero;
    BlendFactor blendDstAlphaFactor = BlendFactor::One;
    bool currentPremultipledAlpha = false;

    struct Texture {
        GLenum type;
        GLuint textureObject;
    };

    unsigned int maxTextures = 0;

    GLenum currentTextureSlot;
    std::map<GLenum, Texture> currentBoundTextures;

    std::map<GLenum, GLuint> emptyTextures;

    Rect<int> currentScissor = { 0, 0, 0, 0 };

    Rect<int> currentViewport = { 0, 0, 0, 0 };

    currentFlipSided = ;
    currentCullFace = ;
    float currentLineWidth = 0.0f;

  
    float currentPolygonOffsetFactor;
    float currentPolygonOffsetUnits;
    // to do
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