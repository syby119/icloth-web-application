#include "image.h"
#include "texture.h"

class TextureCubemap : public Texture {
public:
    TextureCubemap(const Image& imagePositiveX, const Image& imageNegativeX,
                   const Image& imagePositiveY, const Image& imageNegativeY,
                   const Image& imagePositiveZ, const Image& imageNegativeZ,
                   WrapMode wrapS, WrapMode wrapT, WrapMode wrapR,
	               FilterMode minFilter, FilterMode magFilter, 
			       Format format, bool generateMipmaps, int unpackAlignment)
        : Texture(minFilter, magFilter, format, generateMipmaps, unpackAlignment),
          _imagePositiveX(_imagePositiveX), _imageNegativeX(_imageNegativeX), 
          _imagePositiveY(_imagePositiveY), _imageNegativeY(_imageNegativeY), 
          _imagePositiveZ(_imagePositiveZ), _imageNegativeZ(_imageNegativeZ), 
          _wrapS(wrapS), _wrapT(wrapT), _wrapR(wrapR) { }

    TextureCubemap(Image&& imagePositiveX, Image&& imageNegativeX,
                   Image&& imagePositiveY, Image&& imageNegativeY,
                   Image&& imagePositiveZ, Image&& imageNegativeZ,
                   WrapMode wrapS, WrapMode wrapT, WrapMode wrapR,
                   FilterMode minFilter, FilterMode magFilter, 
                   Format format, bool generateMipmaps, int unpackAlignment)
        : Texture(minFilter, magFilter, format, generateMipmaps, unpackAlignment),
          _imagePositiveX(std::move(_imagePositiveX)), 
          _imageNegativeX(std::move(_imageNegativeX)), 
          _imagePositiveY(std::move(_imagePositiveY)), 
          _imageNegativeY(std::move(_imageNegativeY)), 
          _imagePositiveZ(std::move(_imagePositiveZ)), 
          _imageNegativeZ(std::move(_imageNegativeZ)), 
          _wrapS(wrapS), _wrapT(wrapT), _wrapR(wrapR) { }
 {}

    ~Texture2D() = default;

    const Image& getImagePositiveX() const {
        return _imagePositiveX;
    }

    const Image& getImageNegativeX() const {
        return _imageNegativeX;
    }

    const Image& getImagePositiveY() const {
        return _imagePositiveY;
    }
    const Image& getImageNegativeY() const {
        return _imageNegativeY;
    }
    
    const Image& getImagePositiveZ() const {
        return _imagePositiveZ;
    }
    
    const Image& getImageNegativeZ() const {
        return _imageNegativeZ;
    }

    WrapMode getWrapS() const {
        return _wrapS;
    }

    WrapMode getWrapS() const {
        return _wrapS;
    }

    WrapMode getWrapS() const {
        return _wrapS;
    }

private:
    Image _imagePositiveX, _imageNegativeX;
    Image _imagePositiveY, _imageNegativeY;
    Image _imagePositiveZ, _imageNegativeZ;
    WrapMode _wrapS = WrapMode::ClampToEdge;
    WrapMode _wrapT = WrapMode::ClampToEdge;
    WrapMode _wrapR = WrapMode::ClampToEdge;
};