#pragma once

#include <list>
#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../constants.h"
#include "../math/uuid.h"
#include "layers.h"

struct Object3D : public std::enable_shared_from_this<Object3D> {
public:
    static constexpr glm::vec3 xAxis { 1.0f, 0.0f, 0.0f };
    static constexpr glm::vec3 yAxis { 0.0f, 1.0f, 0.0f };
    static constexpr glm::vec3 zAxis { 0.0f, 0.0f, 1.0f };

    static constexpr glm::vec3 defaultFront { 0.0f, 0.0f, -1.0f };
    static constexpr glm::vec3 defaultUp { 0.0f, 1.0f, 0.0f };
    static constexpr glm::vec3 defaultRight { 1.0f, 0.0f, 0.0f };
public:
    // meta info
    const uint32_t id;                                //< unique id starts from 0
    std::string name;                                 //< name of the object
    const UUID uuid = generateUUID();                 //< uuid of the object
    // transformation
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };        //< local position
    glm::quat rotation = { 1.0f, 0.0f, 0.0f, 0.0f };  //< local rotation in quaternion
    glm::vec3 scale    = { 1.0f, 1.0f, 1.0f };        //< local scale
    // scene graph relationship
    std::shared_ptr<Object3D> parent;                 //< parent of this object
    std::list<std::shared_ptr<Object3D>> children;    //< children of this object
    // render related
    RenderMode renderMode = RenderMode::Triangles;    //< render mode of the object
    uint32_t renderOrder = 0;                         //< render order of the objcet
    uint32_t visible = true;                          //< visibility
    bool frustumCulled = false;                       //< enable frustrum culling
    Layers layers;                                    //< layers
public:
    Object3D();

    Object3D(const Object3D& rhs);

    Object3D(Object3D&& rhs) noexcept = delete;

    virtual ~Object3D() = default;

    Object3D& operator=(const Object3D& rhs);

    Object3D& operator=(Object3D&& rhs) noexcept = delete;

    glm::vec3 getFront() const;

    glm::vec3 getUp() const;

    glm::vec3 getRight() const;

    glm::mat4 getMatrix() const;

    glm::mat4 getWorldMatrix() const;

    void translate(const glm::vec3& direction, float distance);

    void translateX(float distance);

    void translateY(float distance);

    void translateZ(float distance);

    void rotate(const glm::vec3& axis, float angle);

    void rotateX(float angle);

    void rotateY(float angle);

    void rotateZ(float angle);

    void lookAt(const glm::vec3& worldTargetPosition);

    std::shared_ptr<Object3D> getObjectById(uint32_t id) const;

    std::shared_ptr<Object3D> getObjectByName(const std::string& name) const;

    bool add(std::shared_ptr<Object3D> child);

    bool attach(std::shared_ptr<Object3D> child);

    bool remove(std::shared_ptr<Object3D> child, bool recursive = false);

    bool removeFromParent();

    uint32_t getDepth() const;

    void printInfo(bool recursive = false) const;
private:
    void _compatibleCopy(const Object3D& rhs);
};