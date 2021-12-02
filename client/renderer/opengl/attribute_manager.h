#pragma once

#include <map>
#include <memory>
#include <iostream>

#include <glad/glad.h>

#include "constant_interpret.h"
#include "buffer.h"
#include "core/buffer_attribute.hpp"

namespace gl {
class AttributeManager {
public:
    AttributeManager() = default;

    ~AttributeManager() = default;

    template <typename T>
    std::shared_ptr<Buffer> get(const BufferAttribute<T>& attribute);

    template <typename T>
    bool remove(const BufferAttribute<T>& attribute);

    template <typename T>
    void update(BufferAttribute<T>& attribute, GLenum bufferType);
private:
    // attribute.id => gl::Buffer
    std::map<uint32_t, std::shared_ptr<Buffer>> _map;
};
}

namespace gl {
template <typename T>
std::shared_ptr<Buffer> AttributeManager::get(const BufferAttribute<T>& attribute) {
    // TODO: add interleaved buffer attribute support
    auto& iter = _map.find(attribute.getId());
    return iter != _map.end() ? * iter : nullptr;
}

template <typename T>
bool AttributeManager::remove(const BufferAttribute<T>& attribute) {
    // ToDo: support InterleavedBufferAttribute
    auto& iter = _map.find(attribute);

    if (iter != _map.end()) {
        iter->second.reset();
        _map.erase(iter);
        return true;
    } else {
        return false;
    }
}

template <typename T>
void AttributeManager::update(BufferAttribute<T>& attribute, GLenum bufferType) {
    // ToDo: support GLBufferAttribute
    // ToDo: support InterleavedBufferAttribute
    // ToDo: support updateRange not { 0, -1 }
    const uint32_t id = attribute.getId();
    auto& iter = _map.find(id);

    if (iter == _attributeBufferMap.end()) {
        _attributeBufferMap[id] = std::make_shared<Buffer>(
                                      bufferType, 
                                      attribute.getDataPtr(),
                                      interpret(attribute.getDataType()),
                                      attribute.getItemStride(),
                                      attribute.getItemCount(),
                                      interpret(attribute.getUsage()),
                                      attribute.getVersion());
    } else {
        std::shared_ptr<Buffer> buffer = iter->second;
        const uint32_t version = attribute.getVersion();
        if (buffer->getVersion() < version) {
            auto range = attribute.getUpdateRange();
            buffer->update(attribute.getDataPtr(), range.offset, range.count);
            attribute.setUpdateRange(0, 0);
            buffer->setVersion(version);
        }
    }
}
}