#pragma once

#include <memory>
#include <vector>

#include <glm.hpp>

#include "object3d.h"

#include "texture.h"
// #include "importer.h"
// #include "model.h"

class Scene : public Object3D {
public:
    Scene() = default;

    ~Scene() = default;

private:
    // std::unique_ptr<Importer> importer;
    // std::vector<std::shared_ptr<Light>> lights;
    // std::vector<std::shared_ptr<Model>> models; 
    std::vector<std::shared_ptr<Texture>> textures;
};