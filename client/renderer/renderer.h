#pragma once

#include <glm/glm.hpp>

#include "camera/camera.h"
#include "scene/scene.h"
#include "render_target.h"

class Renderer {
public:
    enum class RenderMode {
        Point,
        Line,
        LineStrip,
        Triangle,
        TriangleStrip,
        TriangleFan
    };
public:
    Renderer(bool antialias) { }

    ~Renderer() { }

    void render(const Scene& scene, const Camera& camera) {

    }

private:
    RenderMode _mode = RenderMode::Triangle;
    glm::vec4 _clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
    bool _antialias = false;
    int _width = 0, _height = 0;
};