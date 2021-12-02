#pragma once

#include <vector>
#include <cstring>

#include "../constants.h"

inline uint32_t __generateBufferAttributeID() {
    static int gid = 0;
    return gid++;
}

template <typename T>
class BufferAttribute {
public:
    struct Range {
        int offset;
        int count;
    };
public:
    BufferAttribute(void*&& data, DataType type, 
                    uint32_t itemSize, uint32_t itemStride, 
                    BufferUsage usage);

    BufferAttribute(const std::vector<T>& items, DataType type, 
                    uint32_t itemStride, BufferUsage usage);

    BufferAttribute(const BufferAttribute& rhs);

    BufferAttribute(BufferAttribute&& rhs) noexcept;

    ~BufferAttribute();

    BufferAttribute& operator=(const BufferAttribute& rhs);

    BufferAttribute& operator=(BufferAttribute&& rhs) noexcept;

    bool isValid() const;

    operator bool() const;

    uint32_t getId() const;

    T& operator[](uint32_t index);

    const T& operator[](uint32_t index) const;

    void* getDataPtr() const;

    void getDataType() const;

    uint32_t getItemCount() const;

    uint32_t getItemStride() const;

    uint32_t getBufferSize() const;

    BufferUsage getUsage() const;

    uint32_t getVersion() const;

    void updateVersion();

    Range getUpdateRange() const;

    void setUpdateRange(int offset, int count);
private:
    const uint32_t _id = __generateBufferAttributeID(); //< id
    char* _data = nullptr;                              //< data storage
    DataType _dataType = DataType::Float;               //< data type of the storage

    uint32_t _itemCount = 0;                            //< item count
    uint32_t _itemStride = 0;                           //< item stride in data buffer
    BufferUsage _usage = BufferUsage::StaticDraw;       //< render usage

    uint32_t _version = 0;                              //< version for update
    Range updateRange = { 0, -1 };                      //< update range
};

template <typename T>
BufferAttribute<T>::BufferAttribute(void*&& data, DataType type, 
                                    uint32_t itemSize, uint32_t itemStride, 
                                    BufferUsage usage) 
    : _data(reinterpret_cast<char*>(data)), _type(type),
      _itemSize(itemSize), _itemStride(itemStride), _usage(usage) { }

template <typename T>
BufferAttribute<T>::BufferAttribute(const std::vector<T>& items, DataType type, 
                                    uint32_t itemStride, BufferUsage usage)
    : _data(new char[itemStride * items.size()]), 
      _itemCount(items.size()), _itemStride(itemStride), 
      _usage(usage) {
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
uint32_t BufferAttribute<T>::getId() const {
    return _id;
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
BufferUsage BufferAttribute<T>::getUsage() const {
    return _usage;
}

template <typename T>
uint32_t BufferAttribute<T>::getVersion() const {
    return _version;
}

template <typename T>
void BufferAttribute<T>::updateVersion() {
    ++_version;
}

template <typename T>
BufferAttribute<T>::Range BufferAttribute<T>::getUpdateRange() const {
    return _updateRange;
}

template <typename T>
void BufferAttribute<T>::setUpdateRange(int offset, int count) {
    _updateRange = { offset, count }
}