#include <stack>
#include <queue>
#include <iostream>

#include "object3d.h"

static inline uint32_t generateObjectID() noexcept {
    static uint32_t objectID = 0;
    return ++objectID;
}

Object3D::Object3D(): _id(generateObjectID()) { }

Object3D::Object3D(const Object3D& rhs): _id(generateObjectID()) {
    _compatibleCopy(rhs);
}

Object3D& Object3D::operator=(const Object3D& rhs) {
    _compatibleCopy(rhs);
}

uint32_t Object3D::getID() const {
    return _id;
}

std::string Object3D::getName() const {
    return _name;
}

void Object3D::setName(std::string name) {
    _name = name;
}

UUID Object3D::getUUID() const {
    return _uuid;
}

glm::vec3 Object3D::getFront() const {
    return _rotation * defaultFront;
}

glm::vec3 Object3D::getUp() const {
    return _rotation * defaultUp;
}

glm::vec3 Object3D::getRight() const {
    return _rotation * defaultRight;
}

glm::vec3 Object3D::getPosition() const {
    return _position;
}

void Object3D::setPosition(const glm::vec3& position) {
    _position = position;
}

glm::quat Object3D::getRotation() const {
    return _rotation;
}

void Object3D::setRotation(const glm::quat& rotation) {
    _rotation = rotation;
}

glm::vec3 Object3D::getScale() const {
    return _scale;
}

void Object3D::setScale(const glm::vec3& scale) {
    _scale = scale;
}

glm::mat4 Object3D::getMatrix() const {
    return glm::translate(glm::mat4(1.0f), _position) *
        glm::mat4_cast(_rotation) *
        glm::scale(glm::mat4(1.0f), _scale);
}

glm::mat4 Object3D::getWorldMatrix() const {
    glm::mat4 m = getMatrix();
    for (Object3D* p = _parent; p != nullptr; p = p->_parent) {
        m = p->getMatrix() * m;
    }

    return m;
}

void Object3D::updateWorldMatrix(bool recursive) {
    // update parents world matrix until
    for (Object3D* p = _parent; p != nullptr; p = p->_parent) {
        if (p->_worldMatrixNeedsUpdate) {
            
        }
    }

}

void Object3D::translate(const glm::vec3& direction, float distance) {
    _position += direction * distance;
}

void Object3D::translateX(float distance) {
    _position.x += distance;
}

void Object3D::translateY(float distance) {
    _position.y += distance;
}

void Object3D::translateZ(float distance) {
    _position.z += distance;
}

void Object3D::rotate(const glm::vec3& axis, float angle) {
    _rotation = glm::angleAxis(angle, axis) * _rotation;
}

void Object3D::rotateX(float angle) {
    _rotation = glm::angleAxis(angle, xAxis) * _rotation;
}

void Object3D::rotateY(float angle) {
    _rotation = glm::angleAxis(angle, yAxis) * _rotation;
}

void Object3D::rotateZ(float angle) {
    _rotation = glm::angleAxis(angle, zAxis) * _rotation;
}

void Object3D::lookAt(const glm::vec3& worldTargetPosition) {
    // TODO: get front direction point at the world target position
    assert(0);
}

Object3D* Object3D::getObjectById(uint32_t id) const {
    std::stack<const Object3D*> stack({this});
    const Object3D* target = nullptr;
    
    while (!stack.empty()) {
        target = stack.top();
        if (target->_id == id) {
            break;
        }

        stack.pop();
        for (const auto child : target->_children) {
            stack.push(child);
        }
    }
    
    return target->_id == id ? const_cast<Object3D*>(target) : nullptr;
}

Object3D* Object3D::getObjectByName(const std::string& name) const {
    std::queue<const Object3D*> queue({ this });
    const Object3D* target = nullptr;
    bool found = false;

    while (!queue.empty()) {
        target = queue.front();
        if (target->_name == name) {
            found = true;
            break;
        }

        queue.pop();
        for (const auto child : target->_children) {
            queue.push(child);
        }
    }

    return found ? const_cast<Object3D*>(target) : nullptr;
}

bool Object3D::add(Object3D* child) {
    if (child == nullptr || child == this) {
        return false;
    }

    if (child->_parent != nullptr) {
        child->_parent->remove(child);
    }

    child->_parent = this;
    _children.push_back(child);

    return true;
}

bool Object3D::attach(Object3D* child) {
    // TODO: attach the child to the current object while maintain its world position
    assert(0);
    return false;
}

bool Object3D::remove(Object3D* child, bool recursive) {
    for (const auto c : _children) {
        if (c == child) {
            _children.remove(child);
            return true;
        }
    }

    if (recursive) {
        for (const auto c : _children) {
            if (remove(c, recursive)) {
                return true;
            }
        }
    }

    return false;
}

bool Object3D::removeFromParent() {
    if (_parent != nullptr) {
        _parent->remove(this, false);
        return true;
    }

    return false;
}

void Object3D::_compatibleCopy(const Object3D& rhs) {
    _name = rhs._name;
    _position = rhs._position;
    _rotation = rhs._rotation;
    _scale = rhs._scale;
    _parent = rhs._parent;
    if (_parent != nullptr) {
        _parent->add(this);
    }
}

uint32_t Object3D::getDepth() const {
    uint32_t depth = 0;
    for (Object3D* p = _parent; p != nullptr; p = p->_parent) {
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

        std::cout << "id:       " << object->_id << '\n';
        std::cout << "name:     " << object->_name << '\n';
        std::cout << "uuid:     " << uuidToHexString(object->_uuid) << '\n';
        std::cout << "position: "; printVec3(object->_position); std::cout << '\n';
        std::cout << "rotaion:  "; printQuat(object->_rotation); std::cout << '\n';
        std::cout << "scale:    "; printVec3(object->_scale);    std::cout << '\n';

        std::cout << "parent:   "; 
        if (object->_parent != NULL) {
            std::cout << object->_parent->_id << '\n';
        } else {
            std::cout << "NULL\n";
        }

        std::cout << "children: [";
        bool first = true;
        for (const auto child : object->_children) {
            if (first) {
                std::cout << child->_id;
                first == false;
            } else {
                std::cout << ", " << child->_id;
            }
        }
        std::cout << ']\n';
    };

    uint32_t depth = getDepth();
    std::queue<const Object3D*> queue({ this });
    uint32_t lastID = _id;

    std::cout << "############### Object Info ###############\n";
    while (!queue.empty()) {
        const Object3D* obj = queue.front();
        queue.pop();
        for (const auto child : obj->_children) {
            queue.push(child);
        }

        if (obj->_id == lastID) {
            std::cout << "--------------- Depth " << depth++ << "---------------\n";
            lastID = queue.back()->_id;
        }

        printNode(obj);
        std::cout << '\n';
    }
}