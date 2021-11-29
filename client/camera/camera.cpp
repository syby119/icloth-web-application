#include "camera.h"

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + getFront(), getUp());
}