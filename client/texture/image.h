#pragma once

class Image {
public:
    enum class Type {
        Int8,
        Uint8,
        Int16,
        Uint16,
        HalfFloat,
        Float,
    };

public:
    Image(void* data, int width, int height, int channels, Type type);

    Image(const Image& image);

    Image(Image&& image) noexcept;

    ~Image();

    Image& operator=(const Image& image);

    Image& operator=(Image&& image) noexcept;

    size_t getTotalBytes() const;

private:
    char* _data = nullptr;
    int _width = 0;
    int _height = 0;
    int _channels = 0;
    Type _type = Type::Uint8;
}