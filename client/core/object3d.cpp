#include <stack>
#include <queue>
#include <iostream>

#include "object3d.h"

static inline uint32_t generateObjectID() noexcept {
    static uint32_t objectID = 0;
    return ++objectID;
}

Object3D::Object3D(): id(generateObjectID()) { }

Object3D::Object3D(const Object3D& rhs): id(generateObjectID()) {
    _compatibleCopy(rhs);
}

Object3D& Object3D::operator=(const Object3D& rhs) {
    _compatibleCopy(rhs);
}

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
    for (const Object3D* p = parent.get(); p; p = p->parent.get()) {
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

void Object3D::lookAt(const glm::vec3& worldTargetPosition) {
    // TODO: get front direction point at the world target position
    assert(0);
}

std::shared_ptr<Object3D> Object3D::getObjectById(uint32_t id) const {
    std::stack<const Object3D*> stack({ this });

    while (!stack.empty()) {
        auto object = const_cast<Object3D*>(stack.top());
        if (object->id == id) {
            return object->shared_from_this();
        }

        stack.pop();
        for (const auto child : object->children) {
            stack.push(child.get());
        }
    }
    
    return nullptr;
}

std::shared_ptr<Object3D> Object3D::getObjectByName(const std::string& name) const {
    std::queue<const Object3D*> queue({ this });

    while (!queue.empty()) {
        auto object = const_cast<Object3D*>(queue.front());
        if (object->name == name) {
            return object->shared_from_this();
        }

        queue.pop();
        for (const auto child : object->children) {
            queue.push(child.get());
        }
    }

    return nullptr;
}

bool Object3D::add(std::shared_ptr<Object3D> child) {
    if (!child || child.get() == this) {
        return false;
    }

    if (child->parent) {
        child->parent->remove(child);
    }

    child->parent = shared_from_this();
    children.push_back(child);

    return true;
}

bool Object3D::attach(std::shared_ptr<Object3D> child) {
    // TODO: attach the child to the current object while maintain its world position
    assert(0);
    return false;
}

bool Object3D::remove(std::shared_ptr<Object3D> child, bool recursive) {
    for (const auto c : children) {
        if (c == child) {
            children.remove(child);
            child->parent.reset();
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

bool Object3D::removeFromParent() {
    if (parent) {
        parent->remove(shared_from_this(), false);
        return true;
    }

    return false;
}

void Object3D::_compatibleCopy(const Object3D& rhs) {
    name = rhs.name;
    position = rhs.position;
    rotation = rhs.rotation;
    scale = rhs.scale;
    parent = rhs.parent;
    if (parent) {
        parent->add(shared_from_this());
    }
    layers = rhs.layers;
}

uint32_t Object3D::getDepth() const {
    uint32_t depth = 0;

    for (const Object3D* p = parent.get(); p; p = p->parent.get()) {
        ++depth;
    }

    return depth;
}

void Object3D::printInfo(bool recursive) const {
    auto printNode = [](const Object3D* object) {
        auto printVec3 = [](const glm::vec3& v) {
            std::cout << "(" << v.x  << "," << v.y << "," << v.z << ")";
        };

        auto printQuat = [](const glm::quat& q) {
            std::cout << "(" << q.w << "," << q.x  << "," << q.y << "," << q.z << ")";
        };

        std::cout << "id:       " << object->id << '\n';
        std::cout << "name:     " << object->name << '\n';
        std::cout << "uuid:     " << uuidToHexString(object->uuid) << '\n';
        std::cout << "position: "; printVec3(object->position); std::cout << '\n';
        std::cout << "rotaion:  "; printQuat(object->rotation); std::cout << '\n';
        std::cout << "scale:    "; printVec3(object->scale);    std::cout << '\n';

        std::cout << "parent:   "; 
        if (object->parent != NULL) {
            std::cout << object->parent->id << '\n';
        } else {
            std::cout << "NULL\n";
        }

        std::cout << "children: [";
        bool first = true;
        for (const auto child : object->children) {
            if (first) {
                std::cout << child->id;
                first == false;
            } else {
                std::cout << ", " << child->id;
            }
        }
        std::cout << ']\n';
    };

    uint32_t depth = getDepth();
    std::queue<const Object3D*> queue({ this });
    uint32_t lastID = id;

    std::cout << "############### Object Info ###############\n";
    while (!queue.empty()) {
        const Object3D* obj = queue.front();
        queue.pop();
        for (const auto child : obj->children) {
            queue.push(child.get());
        }

        if (obj->id == lastID) {
            std::cout << "--------------- Depth " << depth++ << "---------------\n";
            lastID = queue.back()->id;
        }

        printNode(obj);
        std::cout << '\n';
    }
}