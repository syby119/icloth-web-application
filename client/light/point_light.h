#pragma once

#include "light.h"

class PointLight : 

class SpotLight : public Light {
public:
	SpotLight() = default;

	~SpotLight() = default;

public:
	float angle = glm::radians(60.0f);
	float kc = 1.0f;
	float kl = 0.0f;
	float kq = 0.2f;
};