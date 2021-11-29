#pragma once

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"

namespace gl {
class Program {
public:
    Program(const char* vsCode, const char* fsCode);

    Program(const std::string& vsFilepath, const std::string& fsFilepath);

    Program(Program&& program) noexcept;

    ~Program();

    void use();
private:
    GLuint _handle = 0;

    std::string readFile(const std::string& filePath);

    GLuint createShader(const std::string& code, GLenum shaderType);

    void createShaderProgram(const std::string& vsCode, const std::string& fsCode);
};
} // ! namespace gl