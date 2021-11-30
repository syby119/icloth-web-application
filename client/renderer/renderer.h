#pragma once

#include <glm/glm.hpp>

#include "../math/rect.h"

#include "camera/camera.h"
#include "scene/scene.h"
#include "render_target.h"
#include "state.h"

enum class RenderMode {
    Point,
    Line,
    LineStrip,
    Triangle,
    TriangleStrip,
    TriangleFan
};

class Renderer {
public:
    bool autoClear = true;
    bool autoClearColor = true;
    bool autoClearDepth = true;
    bool autoClearStencil = true;
    // scene graph
    bool sortObjects = true;

    // this.clippingPlanes = [];
    // this.localClippingEnabled = false; // physically based shading
    // this.gammaFactor = 2.0; // for backwards compatibility
    // this.outputEncoding = LinearEncoding; // physical lights

    // this.physicallyCorrectLights = false; // tone mapping

    // this.toneMapping = NoToneMapping;
    // this.toneMappingExposure = 1.0; // internal properties

public:
    Renderer(bool antialias);

    ~Renderer();

    void render(const Scene& scene, const Camera& camera);

    void clear(bool color = true, bool depth = true, bool stencil = true);

    void clearColor();

    void clearDepth();

    void clearStencil();

    Rect<int> getViewport() const;

    void setViewport(Rect<int> viewport);

    bool getScissorTest() const;

    void setScissorTest(bool enable);

    Rect<int> getScissor() const;

    void setScissor(Rect<int> scissor);

    // void getClearColor();

    // void setClearColor();

private:


    // let _currentActiveCubeFace = 0;
    // let _currentActiveMipmapLevel = 0;
    // let _currentRenderTarget = null;


    // let _currentMaterialId = -1;

    // let _currentCamera = null;

    // const _currentViewport = new Vector4();

    // const _currentScissor = new Vector4();

    // let _currentScissorTest = null; //

    // let _width = _canvas.width;
    // let _height = _canvas.height;
    // let _pixelRatio = 1;
    // let _opaqueSort = null;
    // let _transparentSort = null;

    int _width, _height;
    float _pixelRatio = 1.0f;

    Rect<int> _viewport;

    bool _scissorTest = false;
    Rect<int> _scissor;

    // let _scissorTest = false;

    // const _currentDrawBuffers = []; // frustum

    // const _frustum = new Frustum(); // clipping

    // let _clippingEnabled = false;
    // let _localClippingEnabled = false; // transmission

    // let _transmissionRenderTarget = null; // camera matrices cache

    // const _projScreenMatrix = new Matrix4();
private:
    gl::State _state;

    void _initGL();

    void _projectObject();
};