#pragma once

#include <vector>

#include "core/object3d.h"
#include "core/buffer_geometry.h"
#include "material/material.h"

struct Mesh : public Object3D {
public:
    BufferGeometry geometry;
    std::vector<Material> materials;
};