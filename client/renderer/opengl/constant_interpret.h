#pragma once

#include <glad/glad.h>

#include "../constants.h"

namespace gl {
inline GLboolean interpret(bool flag) noexcept {
    return flag ? GL_TRUE : GL_FALSE;
}

inline GLenum interpret(TestFunc testFunc) noexcept {
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

inline GLenum interpret(StencilOp op) noexcept {
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