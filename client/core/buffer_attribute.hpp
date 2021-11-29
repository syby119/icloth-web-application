#pragma once

#include <vector>
#include <cstring>

template <typename T>
class BufferAttribute {
public:
    enum class Usage { StaticDraw, DynamicDraw, StreamDraw };

    BufferAttribute(void*&& data, uint32_t itemSize, uint32_t itemStride, Usage usage);

    BufferAttribute(const std::vector<T>& items, uint32_t itemStride, Usage usage);

    BufferAttribute(const BufferAttribute& rhs);

    BufferAttribute(BufferAttribute&& rhs) noexcept;

    ~BufferAttribute();

    BufferAttribute& operator=(const BufferAttribute& rhs);

    BufferAttribute& operator=(BufferAttribute&& rhs) noexcept;

    bool isValid() const;

    operator bool() const;

    T& operator[](uint32_t index);

    const T& operator[](uint32_t index) const;

    void* getDataPtr() const;

    uint32_t getItemCount() const;

    uint32_t getItemStride() const;

    uint32_t getBufferSize() const;

    Usage getUsage() const;

    bool getUpdated() const;

    void setUpdated(bool updated);

private:
    char* _data          = nullptr;  //< data storage
    uint32_t _itemCount  = 0;        //< item count
    uint32_t _itemStride = 0;        //< item stride in data buffer
    Usage _usage         = Usage::StaticDraw;
    bool _updated = false;
};

template <typename T>
BufferAttribute<T>::BufferAttribute(void*&& data, uint32_t itemSize, uint32_t itemStride, Usage usage) 
    : _data(reinterpret_cast<char*>(data)), 
      _itemSize(itemSize), _itemStride(itemStride), _usage(usage) { }

template <typename T>
BufferAttribute<T>::BufferAttribute(const std::vector<T>& items, uint32_t itemStride, Usage usage)
    : _data(new char[itemStride * items.size()]), 
      _itemCount(items.size()), _itemStride(itemStride), 
      _usage(usage), _updated(true) {
    assert(itemStride >= sizeof(T));

    for (size_t i = 0; i < items.size(); ++i) {
        *reinterpret_cast<T*>(_data + i * _itemStride) = items[i];
    }
}

template <typename T>
BufferAttribute<T>::BufferAttribute(const BufferAttribute& rhs) {
    size_t byteLength = static_cast<size_t>(rhs.itemCount) * rhs.itemStride;
    delete[] _data; _data = new char[byteLength];
    std::memcpy(_data, rhs._data, byteLength);
    _updated = true;
}

template <typename T>
BufferAttribute<T>::BufferAttribute(BufferAttribute&& rhs) noexcept {
    delete[] _data; _data = rhs._data; rhs_data = nullptr;
    _itemCount = rhs._itemCount; rhs._itemCount = 0;
    _itemStride = rhs._itemStride; rhs._itemStride = 0;
    _usage = rhs._usage;
    _update = true;
}

template <typename T>
BufferAttribute<T>::~BufferAttribute() {
    if (_data) {
        delete[] _data;
        _data = nullptr;
    }
}

template <typename T>
BufferAttribute<T>& BufferAttribute<T>::operator=(const BufferAttribute<T>& rhs) {
    if (this != &rhs) {
        delete[] _data;
        size_t byteLength = static_cast<size_t>(rhs->itemCount) * rhs->itemStride;
        _data = new char[byteLength];
        std::memcpy(_data, rhs->_data, byteLength);

        _itemCount = rhs._itemCount;
        _itemStride = rhs._itemStride;
        _usage = rhs._usage;
        _update = true;
    }

    return *this;
}

template <typename T>
BufferAttribute<T>& BufferAttribute<T>::operator=(BufferAttribute<T>&& rhs) noexcept {
    if (this != &rhs) {
        delete[] _data;
        _data = rhs->_data;
        _itemCount = rhs->_itemCount;
        _itemStride = rhs->_itemStride;
        _usage = rhs->_usage;
        _update = true;
    }

    return *this;
}

template <typename T>
bool BufferAttribute<T>::isValid() const {
    return _data == nullptr;
}

template <typename T>
BufferAttribute<T>::operator bool() const {
    return isValid();
}

template <typename T>
T& BufferAttribute<T>::operator[](uint32_t index) {
    return *reinterpret_cast<T*>(_data + index * _itemStride);
}

template <typename T>
const T& BufferAttribute<T>::operator[](uint32_t index) const {
    return *reinterpret_cast<T*>(_data + index * _itemStride);
}

template <typename T>
void* BufferAttribute<T>::getDataPtr() const {
    return _data;
}

template <typename T>
uint32_t BufferAttribute<T>::getItemCount() const {
    return _itemCount;
}

template <typename T>
uint32_t BufferAttribute<T>::getItemStride() const {
    return _itemStride;
}
template <typename T>

uint32_t BufferAttribute<T>::getBufferSize() const {
    return _itemCount * _itemStride;
}

template <typename T>
BufferAttribute<T>::Usage BufferAttribute<T>::getUsage() const {
    return _usage;
}

template <typename T>
bool BufferAttribute<T>::getUpdated() const {
    return updated;
}

template <typename T>
void BufferAttribute<T>::setUpdated(bool updated) {
    _updated = updated;
}