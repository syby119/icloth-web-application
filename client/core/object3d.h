#pragma once

#include <list>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct Object3D {
public:
	static constexpr glm::vec3 xAxis { 1.0f, 0.0f, 0.0f };
	static constexpr glm::vec3 yAxis { 0.0f, 1.0f, 0.0f };
	static constexpr glm::vec3 zAxis { 0.0f, 0.0f, 1.0f };

	static constexpr glm::vec3 defaultFront { 0.0f, 0.0f, -1.0f };
	static constexpr glm::vec3 defaultUp { 0.0f, 1.0f, 0.0f };
	static constexpr glm::vec3 defaultRight { 1.0f, 0.0f, 0.0f };
public:
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };        //< local position
	glm::quat rotation = { 1.0f, 0.0f, 0.0f, 0.0f };  //< local rotation in quaternion
	glm::vec3 scale    = { 1.0f, 1.0f, 1.0f };        //< local scale

	Object3D* parent   = nullptr;                     //< parent of this object
	std::list<Object3D*> children;                    //< children of this object

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

	void lookAt(glm::vec3 worldTargetPosition);

	bool add(Object3D* child);

	bool remove(Object3D* child, bool recursive = false);
};