#include "object3d.h"

glm::vec3 Object3D::getFront() const {
    return rotation * defaultFront;
}

glm::vec3 Object3D::getUp() const {
    return rotation * defaultUp;
}

glm::vec3 Object3D::getRight() const {
    return rotation * defaultRight;
}

glm::mat4 Object3D::getMatrix() const {
    return glm::translate(glm::mat4(1.0f), position) *
        glm::mat4_cast(rotation) *
        glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Object3D::getWorldMatrix() const {
    glm::mat4 m = getMatrix();
    for (Object3D* p = parent; p != nullptr; p = p->parent) {
        m = p->getMatrix() * m;
    }

    return m;
}

void Object3D::translate(const glm::vec3& direction, float distance) {
    position += direction * distance;
}

void Object3D::translateX(float distance) {
    position.x += distance;
}

void Object3D::translateY(float distance) {
    position.y += distance;
}

void Object3D::translateZ(float distance) {
    position.z += distance;
}

void Object3D::rotate(const glm::vec3& axis, float angle) {
    rotation = glm::angleAxis(angle, axis) * rotation;
}

void Object3D::rotateX(float angle) {
    rotation = glm::angleAxis(angle, xAxis) * rotation;
}

void Object3D::rotateY(float angle) {
    rotation = glm::angleAxis(angle, yAxis) * rotation;
}

void Object3D::rotateZ(float angle) {
    rotation = glm::angleAxis(angle, zAxis) * rotation;
}

void Object3D::lookAt(glm::vec3 worldTargetPosition) {
    assert("To Do: Not Implemented");
}

bool Object3D::add(Object3D* child) {
    if (child == nullptr || child == this) {
        return false;
    }

    if (child->parent != nullptr) {
        child->parent->remove(child);
    }

    child->parent = this;
    children.push_back(child);

    return true;
}

bool Object3D::remove(Object3D* child, bool recursive = false) {
    for (const auto c : children) {
        if (c == child) {
            children.remove(child);
            return true;
        }
    }

    if (recursive) {
        for (const auto c : children) {
            if (remove(c, recursive)) {
                return true;
            }
        }
    }

    return false;
}