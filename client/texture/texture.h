#pragma once 

class Texture {
public:
	enum class WrapMode { 
		Repeat, 
		MirroredRepeat, 
		ClampToEdge, 
		ClampToBorder
	};

	enum class FilterMode {
		Linear, 
		Nearest, 
		MipmapNearest, 
		LinearMipmapNearest, 
		NearestMipmapLinear, 
		LinearMipmapLinear
	};

	enum class Format {
		AlphaFormat,
		RGBFormat,
		RGBAFormat,
		DepthFormat,
		DepthStencilFormat
	};
protected:
	WrapMode _wrapS = WrapMode::Repeat;
	WrapMode _wrapT = WrapMode::Repeat;
	FilterMode _minFilter = FilterMode::Linear;
	FilterMode _magFilter = FilterMode::Linear;
	Format _format = Format::RGBAFormat;
	bool _generateMipmaps = false;
	int _unpackAlignment = 1;
public:
	Texture(FilterMode minFilter, FilterMode magFilter, 
			Format format, bool generateMipmaps, int unpackAlignment)
		: _minFilter(minFilter), _magFilter(magFilter), 
		  _format(format), _generateMipmaps(generateMipmaps), _unpackAlignment(unpackAlignment) {}

	~Texture() = default;

	FilterMode getMinFilter() const {
		return _minFilter;
	}

	FilterMode getMagFilter() const {
		return _magFilter;
	}

	Format getFormat() const {
		return _format;
	}

	bool getGenerateMipmaps() const {
		return _generateMipmaps;
	}

	int getUnpackAlignment() const {
		return _unpackAlignment;
	}
};