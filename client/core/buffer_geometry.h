#pragma once

#include <glm/glm.hpp>

#include "buffer_attribute.hpp"

struct BufferGeometry {
public:
    BufferAttribute<glm::vec3> positions;
    BufferAttribute<glm::vec3> normals;
    BufferAttribute<glm::vec2> texcoords;
    BufferAttribute<glm::vec3> tangents;
    BufferAttribute<glm::vec3> bitangents;
    BufferAttribute<glm::vec3> colors;
    BufferAttribute<uint32_t>  indices;
};