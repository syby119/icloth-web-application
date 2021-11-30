#pragma once

enum class RenderFace {
    Front,
    Back,
    Double
};

enum class FrontFace {
    Clockwise,
    CounterClockwise
};

enum class BlendMode {
    Add, 
    Subtract, 
    ReverseSubtract, 
    Min, 
    Max
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

enum class TestFunc {
    Never,
    Less,
    LessEqual,
    Equal,
    NotEqual,
    Greater,
    GreaterEqual,
    Always
};

enum class StencilOp {
    Zero, 
    Keep, 
    Replace, 
    Increment, 
    Decrement, 
    IncrementWrap, 
    DecrementWrap, 
    Invert
};

enum class BufferUsage {
    StaticDraw,
    DynamicDraw,
    StreamDraw,
    StaticRead,
    DynamicRead,
    StreamRead,
    StaticCopy,
    DynamicCopy,
    StreamCopy,
};