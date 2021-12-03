#pragma once 

#include <iostream>
#include <glad/glad.h>

struct Capability {
public:
    const int maxTextures         = queryInt(GL_MAX_TEXTURE_IMAGE_UNITS);
    const int maxVertexTextures   = queryInt(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS) ;
    const int maxTextureSize      = queryInt(GL_MAX_TEXTURE_SIZE);
    const int maxCubemapSize      = queryInt(GL_MAX_CUBE_MAP_TEXTURE_SIZE);
    const int maxAttributes       = queryInt(GL_MAX_VERTEX_ATTRIBS);
    const int maxVaryings         = queryInt(GL_MAX_VARYING_COMPONENTS);
    const int maxVertexUniforms   = queryInt(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
    const int maxFragmentUniforms = queryInt(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);
    const int maxSamples          = queryInt(GL_MAX_SAMPLES);

    void printInfo() {
        std::cout << "############## OpenGL Capabilities ##############"        << "\n";
        std::cout << "max texture:                     " << maxTextures         << "\n";
        std::cout << "max vertex texture:              " << maxVertexTextures   << "\n";
        std::cout << "max texture size:                " << maxTextureSize      << "\n";
        std::cout << "max cubemap texture size:        " << maxCubemapSize      << "\n";
        std::cout << "max texture image uints:         " << maxAttributes       << "\n";
        std::cout << "max varying components:          " << maxVaryings         << "\n";
        std::cout << "max vertex uniform components:   " << maxVertexUniforms   << "\n";
        std::cout << "max fragment uniform components: " << maxFragmentUniforms << "\n";
        std::cout << "max samples:                     " << maxSamples          << "\n";
    }
private:
    static int queryInt(GLenum name) noexcept {
        int result = 0;
        glGetIntegerv(name, &result);
        return (glGetError() != GL_NO_ERROR) ? result : 0;
    }
};