#pragma once
#include <glad/glad.h>

namespace gl {
class Sampler {
public:
    Sampler() {
        glGenSamplers(1, &_handle);
    }

    ~Sampler() {
        if (_handle != 0) {
            glDeleteSamplers(1, &_handle);
            _handle = 0;
        }
    }
private:
    GLuint _handle = 0;
};

class Sampler2D {
public:
    Sampler2D() = default;

    ~Sampler2D() = default;

    void getWrapS() const;

    void use() const {
        glSamplerParameteri(_handle, GL_TEXTURE_WRAP_S, _wrapS);
        glSamplerParameteri(_handle, GL_TEXTURE_WRAP_T, _wrapT);
        glSamplerParameteri(_handle, GL_TEXTURE_MIN_FILTER, _minFilter);
        glSamplerParameteri(_handle, GL_TEXTURE_MAG_FILTER, _magFilter);
    }
private:
    GLenum _wrapS = GL_REPEAT;
    GLenum _wrapT = GL_REPEAT;
    GLenum _minFilter = GL_NEAREST_MIPMAP_LINEAR;
    GLenum _magFilter = GL_LINEAR;
};

class SamplerCubemap {
public:
    SamplerCubemap();

    ~SamplerCubemap();
private:
    GLenum _wrapS = GL_REPEAT;
    GLenum _wrapT = GL_REPEAT;
    GLenum _wrapR = GL_REPEAT;
    GLenum _minFilter = GL_NEAREST_MIPMAP_LINEAR;
    GLenum _magFilter = GL_LINEAR;
};
}