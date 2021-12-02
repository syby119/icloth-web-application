#pragma once

#include <glad/glad.h>

#include "../../constants.h"

namespace gl {
inline GLboolean interpret(bool flag) noexcept {
    return flag ? GL_TRUE : GL_FALSE;
}

inline GLenum interpret(enum BufferUsage usage) {
    switch (usage) {
        case BufferUsage::StaticDraw:  return GL_STATIC_DRAW;
        case BufferUsage::StaticRead:  return GL_STATIC_READ;
        case BufferUsage::StaticCopy:  return GL_STATIC_COPY;
        case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
        case BufferUsage::DynamicRead: return GL_DYNAMIC_READ;
        case BufferUsage::DynamicCopy: return GL_DYNAMIC_COPY;
        case BufferUsage::StreamRead:  return GL_STREAM_READ;
        case BufferUsage::StreamDraw:  return GL_STREAM_DRAW;
        default:                       return GL_STREAM_COPY;
    }
}

inline GLenum interpret(enum DataType type) {
    switch (type) {
        case DataType::Byte:          return GL_BYTE;
        case DataType::UnsignedByte:  return GL_UNSIGNED_BYTE;
        case DataType::UnsignedShort: return GL_UNSIGNED_SHORT;
        case DataType::Short:         return GL_SHORT;
        case DataType::Int :          return GL_INT;
        case DataType::UnsignedInt :  return GL_UNSIGNED_INT;
        case DataType::HalfFloat :    return GL_HALF_FLOAT;
        case DataType::Float :        return GL_FLOAT;
        default:                      return GL_DOUBLE;
    }
}

inline GLenum interpret(enum TestFunc testFunc) noexcept {
    switch(testFunc) {
        case TestFunc::Never:        return GL_NEVER;
        case TestFunc::Always:       return GL_ALWAYS;
        case TestFunc::Less:         return GL_LESS;
        case TestFunc::LessEqual:    return GL_LEQUAL;
        case TestFunc::Equal:        return GL_EQUAL;
        case TestFunc::GreaterEqual: return GL_GEQUAL;
        case TestFunc::Greater:      return GL_GREATER;
        default:                     return GL_NOTEQUAL;
    }
}

inline GLenum interpret(enum StencilOp op) noexcept {
    switch(op) {
        case StencilOp::Zero:          return GL_ZERO;
        case StencilOp::Keep:          return GL_KEEP;
        case StencilOp::Replace:       return GL_REPLACE;
        case StencilOp::Increment:     return GL_INCR;
        case StencilOp::Decrement:     return GL_DECR;
        case StencilOp::IncrementWrap: return GL_INCR_WRAP;
        case StencilOp::DecrementWrap: return GL_DECR_WRAP;
        default:                       return GL_INVERT;
    }
}
}