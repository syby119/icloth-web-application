#include "renderer.h"

Renderer::Renderer(bool antialias);

void Renderer::render(const Scene& scene, const Camera& camera) {
    _projectObject(scene, camera, 0, sortObjects);
}

void Renderer::_projectObject(
    const Object3D* object, 
    const Camera& camera,
    uint32_t groupOrder,
    bool enableSort) {
    
    // project object recursively
    for ()
}

void Renderer::_renderBufferDirect(
    const Camera& camera,
    const BufferGeometry& geometry,
    const Material& material) {

}

void Renderer::clear(bool color, bool depth, bool stencil) {
    GLbitfield mask = 0;
    if (color)   mask |= GL_COLOR_BUFFER_BIT;
    if (depth)   mask |= GL_DEPTH_BUFFER_BIT;
    if (stencil) mask |= GL_STENCIL_BUFFER_BIT;

    if (mask) {
        glClear(mask);
    }
}

void Renderer::clearColor() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clearDepth() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::clearStencil() {
    glClear(GL_STENCIL_BUFFER_BIT);
}

Rect<int> Renderer::getViewport() const {
    return _viewport;
}

void Renderer::setViewport(Rect<int> viewport) {
    _viewport = viewport;
}

bool Renderer::getScissorTest() const {
    return _scissorTest;
}

void Renderer::setScissorTest(bool enable) {
    _scissorTest = enable;
}

Rect<int> Renderer::getScissor() const {
    return _scissor;
}

void Renderer::setScissor(Rect<int> scissor) {
    _scissor = scissor;
}
