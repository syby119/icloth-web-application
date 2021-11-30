#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "constant_interpret.h"

namespace gl {
class ColorBuffer {
public:
    ColorBuffer() {
        glColorMask(interpret(_colorMask.r), 
                    interpret(_colorMask.g), 
                    interpret(_colorMask.b), 
                    interpret(_colorMask.a));
        glClearColor(_clearColor.r, 
                     _clearColor.g, 
                     _clearColor.b, 
                     _clearColor.a);
    }

    ~ColorBuffer() = default;

    void setMask(glm::bvec4 colorMask) {
        if (_colorMask != colorMask) {
            glColorMask(interpret(colorMask.r), 
                        interpret(colorMask.g),
                        interpret(colorMask.b),
                        interpret(colorMask.a));
            _colorMask = colorMask;
        }
    }

    void setClear(glm::vec4 color, bool premultipiedAlpha = false) {
        if (premultipiedAlpha) {
            color.r *= color.a;
            color.g *= color.a;
            color.b *= color.a;
        }

        if (_clearColor != color) {
            glClearColor(color.r, color.g, color.b, color.a);
            _clearColor = color;
        }
    }

    void reset() {
        _colorMask = glm::bvec4(false, false, false, false);
        _clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
private:
    // glColorMask
    glm::bvec4 _colorMask = { true, true, true, true };
    // glClearColor
    glm::vec4 _clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
};
}