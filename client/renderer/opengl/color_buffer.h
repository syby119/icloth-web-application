#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace gl {
class ColorBuffer {
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
private：
    glm::bvec4 currentColorMask = { false, false, false, false };
    glm::vec4 currentClearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
};
}