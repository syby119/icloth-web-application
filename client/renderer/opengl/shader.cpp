#include <iostream>
#include <stdexcept>

#include "shader.h"

namespace gl {
Shader::Shader(const std::string& code, GLenum type) {
    _handle = glCreateShader(type);
    if (_handle == 0) {
        throw std::runtime_error("create shader failure");
    }

    const char* codeBuf = code.c_str();
    glShaderSource(_handle, 1, &codeBuf, nullptr);
    glCompileShader(_handle);

    GLint success;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        char buffer[1024];
        glGetShaderInfoLog(_handle, sizeof(buffer), nullptr, buffer);
        std::cerr << code << std::endl;
        throw std::runtime_error("compile error: \n" + std::string(buffer));
    }
}

Shader::Shader(Shader&& rhs) {
    _handle = rhs._handle;
    rhs._handle = 0;
}

Shader::~Shader() {
    if (_handle) {
        glDeleteShader(_handle);
        _handle = 0;
    }
}

Shader& Shader::operator=(Shader&& rhs) {
    _handle = rhs._handle;
    rhs._handle = 0;
}

GLuint Shader::getHandle() const {
    return _handle;
}
}