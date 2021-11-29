#pragma once

#include <string>
#include <glad/glad.h>

namespace gl {
class Shader {
public:
    Shader(const std::string& code, GLenum type);

    Shader(const Shader& rhs) = delete;

    Shader(Shader&& rhs);

    ~Shader();

    Shader& operator=(const Shader& rhs) = delete;

    Shader& operator=(Shader&& rhs);

    GLuint getHandle() const;

private:
    GLuint _handle = 0;
};
} // ! namespace gl