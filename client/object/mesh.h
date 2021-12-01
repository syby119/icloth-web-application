#pragma once

#include "core/object3d.h"
#include "core/buffer_geometry.h"
#include "material/material.h"

class Mesh : public Object3D {
public:

private:
    BufferGeometry _geometry;
    Material _material;
};