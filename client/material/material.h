#pragma once

#include "../constants.h"

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

    enum class BlendFactor {
        Zero, 
        One, 
        Src, 
        OneMinusSrc, 
        SrcAlpha, 
        OneMinusSrcAlpha, 
        Dst, 
        OneMinusDst, 
        DstAlpha, 
        OneMinusDstAlpha,
        SrcAlphaSaturate
    };

    enum class BlendEquation {
        Add, 
        Subtract, 
        ReverseSubtract, 
        Min, 
        Max
    };


private:
    bool colorWrite = true;
    Side side = Side::Front;
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
    BlendEquation blendEquation = BlendEquation::Add;

    // dithering
    bool dithering = false;


};