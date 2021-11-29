#include "image.h"
#include "texture.h"

class Texture2D : public Texture {
public:
    Texture2D(const Image &image, WrapMode wrapS, WrapMode wrapT, 
	          FilterMode minFilter, FilterMode magFilter, 
			  Format format, bool generateMipmaps, int unpackAlignment)
        : Texture(minFilter, magFilter, format, generateMipmaps, unpackAlignment),
          _image(image), _wrapS(wrapS), _wrapT(wrapT) { }

    Texture2D(Image &&image, WrapMode wrapS, WrapMode wrapT, 
	          FilterMode minFilter, FilterMode magFilter, 
			  Format format, bool generateMipmaps, int unpackAlignment)
        : Texture(minFilter, magFilter, format, generateMipmaps, unpackAlignment),
          _image(std::move(image)), _wrapS(wrapS), _wrapT(wrapT) { }

    ~Texture2D() = default;

    const Image& getImage() const {
        return _image;
    }

    WrapMode getWrapS() const {
		return _wrapS;
	}

	WrapMode getWrapT() const {
		return _wrapT;
	}
private:
    Image _image;
    WrapMode _wrapS = WrapMode::Repeat;
    WrapMode _wrapT = WrapMode::Repeat;
};