#pragma once

#include "../core/object3d.h"

struct Light : public Object3D {
public:
	Light(const glm::vec3& color, float intensity)
		: _color(color), _intensity(intensity) { }

	Light(int colorInHex, float intensity) {

	}



	~Light() = default;

public:
	glm::vec3 _color = { 1.0f, 1.0f, 1.0f };
	float _intensity = 1.0f;
};