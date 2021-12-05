#pragma once 

#include <glad/glad.h>

namespace gl {
class Texture {
public:
    Texture() {
        glGenTextures(1, &_handle);
    }

    ~Texture() {
        if (_handle != 0) {
            glDeleteTextures(1, &_handle);
            _handle = 0;
        }
    }

    virtual GLenum getType() const noexcept = 0;
private:
    GLuint _handle = 0;
};

class Texture2D {
public:
    Texture2D(GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum magFilter)
        : {
        glBindTextureUnit
        glGenSamplers
        glBindTexture(getType(), _handle);
        glTexParameteri(getType(), GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(getType(), GL_TEXTURE_WRAP_S, wrapT);
	    glTexParameteri(getType(), GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(getType(), GL_TEXTURE_MAG_FILTER, magFilter);
    }

    ~Texture2D() = delete;

    GLenum getType() const noexcept override {
        return GL_TEXTURE_2D;
    }
private:
    GLenum _wrapS;
    GLenum _wrapT;
    GLenum _minFilter;
    GLenum _magFilter;
};

class TextureCubemap {
public:
    TextureCubemap() {

    }

    ~TextureCubemap() = default;

    GLenum getType() const noexcept override {
        return GL_TEXTURE_CUBE_MAP;
    }
private:
};
}