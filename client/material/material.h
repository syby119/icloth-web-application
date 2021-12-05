#pragma once

#include <string>

#include "../constants.h"
#include "../math/uuid.h"

class Material {
public:
    enum class Blending {
        None, 
        Normal, 
        Additive, 
        Subtractive, 
        Multiply, 
        Custom
    };

private:
    // meta data
    const uint32_t id = generateID();
    std::string name;
    UUID uuid = generateUUID();
    // 
    bool fog = false;

    bool colorWrite = true;
    RenderSide renderSide = RenderSide::Front;
    bool visible = true;

    bool polyOffset = false;
    int polyOffsetFactor = 0;
    int polyOffsetUnit = 0;

    // stencil test
    bool stencilWrite = false;
    int stencilMask = 0xFF;
    TestFunc stencilFunc = TestFunc::Always;
    int stencilRef = 0;
    int stencilFuncMask = 0xFF;
    StencilOp stencilFail = StencilOp::Keep;
    StencilOp stencilZFail = StencilOp::Keep;
    StencilOp stencilZPass = StencilOp::Keep;

    // depth test
    bool depthWrite = true;
    TestFunc depthFunc = TestFunc::Less;
    bool depthTest = true;

    // blend
    bool transparent = false;
    float opacity = 1.0f;
    float alphaTest = 0.0f;
    BlendFactor blendSrcFactor = BlendFactor::SrcAlpha;
    BlendFactor blendDstFactor = BlendFactor::OneMinusSrcAlpha;
    bool blendSeparate = false;
    BlendFactor blendSrcAlphaFactor = BlendFactor::Zero;
    BlendFactor blendDstAlphaFactor = BlendFactor::One;
    BlendMode blendMode = BlendMode::Add;
    bool blendAlpha = false;
    BlendMode blendAlphaMode = BlendMode::Add;

    // dithering
    bool dithering = false;

    static inline uint32_t generateID() noexcept {
        static uint32_t gid = 0;
        return ++gid;
    };
};