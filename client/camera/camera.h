#pragma once

#include "../core/object3d.h"

class Camera : public Object3D {
public:
	glm::mat4 getViewMatrix() const;

	virtual glm::mat4 getProjectionMatrix() const = 0;
};