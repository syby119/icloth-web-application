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
    StaticDrawUsage,
    DynamicDrawUsage,
    StreamDrawUsage,
    StaticReadUsage,
    DynamicReadUsage,
    StreamReadUsage,
    StaticCopyUsage,
    DynamicCopyUsage,
    StreamCopyUsage,
};