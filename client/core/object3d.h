#pragma once

#include <list>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../math/uuid.h"

struct Object3D {
public:
    static constexpr glm::vec3 xAxis { 1.0f, 0.0f, 0.0f };
    static constexpr glm::vec3 yAxis { 0.0f, 1.0f, 0.0f };
    static constexpr glm::vec3 zAxis { 0.0f, 0.0f, 1.0f };

    static constexpr glm::vec3 defaultFront { 0.0f, 0.0f, -1.0f };
    static constexpr glm::vec3 defaultUp { 0.0f, 1.0f, 0.0f };
    static constexpr glm::vec3 defaultRight { 1.0f, 0.0f, 0.0f };
public:
    Object3D();

    Object3D(const Object3D& rhs);

    Object3D(Object3D&& rhs) noexcept = delete;

    ~Object3D() = default;

    Object3D& operator=(const Object3D& rhs);

    Object3D& operator=(Object3D&& rhs) noexcept = delete;

    uint32_t getID() const;

    std::string getName() const;

    void setName(std::string name);

    UUID getUUID() const;

    glm::vec3 getFront() const;

    glm::vec3 getUp() const;

    glm::vec3 getRight() const;

    glm::vec3 getPosition() const;

    void setPosition(const glm::vec3& position);

    glm::quat getRotation() const;

    void setRotation(const glm::quat& rotation);

    glm::vec3 getScale() const;

    void setScale(const glm::vec3& scale);

    glm::mat4 getMatrix() const;

    glm::mat4 getWorldMatrix() const;

    void updateWorldMatrix(bool recursive = true);

    void translate(const glm::vec3& direction, float distance);

    void translateX(float distance);

    void translateY(float distance);

    void translateZ(float distance);

    void rotate(const glm::vec3& axis, float angle);

    void rotateX(float angle);

    void rotateY(float angle);

    void rotateZ(float angle);

    void lookAt(const glm::vec3& worldTargetPosition);

    Object3D* getObjectById(uint32_t id) const;

    Object3D* getObjectByName(const std::string& name) const;

    bool add(Object3D* child);

    bool attach(Object3D* child);

    bool remove(Object3D* child, bool recursive = false);

    bool removeFromParent();

    uint32_t getDepth() const;

    void printInfo(bool recursive = false) const;
private:
    // meta info
    const uint32_t _id;                                //< unique id starts from 0
    std::string _name;
    const UUID _uuid = generateUUID();
    // transformation
    glm::vec3 _position = { 0.0f, 0.0f, 0.0f };        //< local position
    glm::quat _rotation = { 1.0f, 0.0f, 0.0f, 0.0f };  //< local rotation in quaternion
    glm::vec3 _scale    = { 1.0f, 1.0f, 1.0f };        //< local scale
    // scene graph relationship
    Object3D* _parent   = nullptr;                     //< parent of this object
    std::list<Object3D*> _children;                    //< children of this object

    void _compatibleCopy(const Object3D& rhs);
};