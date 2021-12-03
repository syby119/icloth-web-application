#pragma once

#include <glad/glad.h>

#include "../../core/object3d.h"
#include "attribute_manager.h"

namespace gl {
class BindingStates {
public:
    BindingStates(AttributeManager& attributes) {
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes);
    }

    ~BindingStates() { }

    void setup(Object3D* object, material, program, geometry, index);

	void reset();
    
	void resetDefaultState();

    void dispose();

	void releaseStatesOfGeometry(geometry);

	void releaseStatesOfProgram(program);

	void initAttributes();

	void enableAttribute(attribute);

	void disableUnusedAttributes();
	}
private:
    int maxVertexAttributes = 0;
    const bindingStates = {};

	const defaultState = createBindingState(null);
	let currentState = defaultState;
private:
	function getBindingState(geometry, program, material) {
		const wireframe = (material.wireframe === true);

		let programMap = bindingStates[geometry.id];
		if (programMap === undefined) {
			programMap = {};
			bindingStates[geometry.id] = programMap;
		}

		let stateMap = programMap[program.id];
		if (stateMap === undefined) {
			stateMap = {};
			programMap[program.id] = stateMap;
		}

		let state = stateMap[wireframe];
		if (state === undefined) {
            GLuint vao = 0;
            glGenVertexArrays(1, &vao);
			state = createBindingState(vao);
			stateMap[wireframe] = state;
		}

		return state;
	}

	function createBindingState(vao) {
		const newAttributes = [];
		const enabledAttributes = [];
		const attributeDivisors = [];

		for (let i = 0; i < maxVertexAttributes; i ++) {
			newAttributes[i] = 0;
			enabledAttributes[i] = 0;
			attributeDivisors[i] = 0;
		}

		return {
			// for backward compatibility on non-VAO support browser
			geometry: null,
			program: null,
			wireframe: false,

			newAttributes: newAttributes,
			enabledAttributes: enabledAttributes,
			attributeDivisors: attributeDivisors,
			object: vao,
			attributes: {},
			index: null
		};
	}

	bool needsUpdate(geometry, index) {
		const cachedAttributes = currentState.attributes;
		const geometryAttributes = geometry.attributes;

		let attributesNum = 0;
		for (const key in geometryAttributes) {
			const cachedAttribute = cachedAttributes[key];
			const geometryAttribute = geometryAttributes[key];

			if (cachedAttribute === undefined) return true;

			if (cachedAttribute.attribute !== geometryAttribute) return true;

			if (cachedAttribute.data !== geometryAttribute.data) return true;

			attributesNum ++;
		}

		if (currentState.attributesNum !== attributesNum) return true;

		if (currentState.index !== index) return true;

		return false;
	}

	void saveCache(geometry, index) {
		const cache = {};
		const attributes = geometry.attributes;
		let attributesNum = 0;

		for (const key in attributes) {
			const attribute = attributes[key];

			const data = {};
			data.attribute = attribute;

			if (attribute.data) {
				data.data = attribute.data;
			}

			cache[key] = data;
			attributesNum ++;
		}

		currentState.attributes = cache;
		currentState.attributesNum = attributesNum;
		currentState.index = index;
	}

	void enableAttributeAndDivisor(attribute, meshPerAttribute) {
		const newAttributes = currentState.newAttributes;
		const enabledAttributes = currentState.enabledAttributes;
		const attributeDivisors = currentState.attributeDivisors;

		newAttributes[attribute] = 1;

		if (enabledAttributes[attribute] === 0) {
			gl.enableVertexAttribArray(attribute);
			enabledAttributes[attribute] = 1;
		}

		if (attributeDivisors[attribute] !== meshPerAttribute) {
            glVertexAttribDivisor(attribute, meshPerAttribute);
			attributeDivisors[attribute] = meshPerAttribute;
		}
	}

	void vertexAttribPointer(index, size, type, normalized, stride, offset) {
		if (type === GL_INT || type === GL_UNSIGNED_INT) {
			glVertexAttribIPointer(index, size, type, stride, offset);
		} else {
			glVertexAttribPointer(index, size, type, normalized, stride, offset);
		}
	}

	void setupVertexAttributes(object, material, program, geometry) {
		initAttributes();

		const geometryAttributes = geometry.attributes;

		const programAttributes = program.getAttributes();

		const materialDefaultAttributeValues = material.defaultAttributeValues;

		for (const name in programAttributes) {
			const programAttribute = programAttributes[name];

			if (programAttribute.location >= 0) {
				let geometryAttribute = geometryAttributes[name];

				if (geometryAttribute === undefined) {
					if (name === 'instanceMatrix' && object.instanceMatrix) geometryAttribute = object.instanceMatrix;
					if (name === 'instanceColor' && object.instanceColor) geometryAttribute = object.instanceColor;
				}

				if (geometryAttribute !== undefined) {
					const normalized = geometryAttribute.normalized;
					const size = geometryAttribute.itemSize;

					const attribute = attributes.get(geometryAttribute);

					if (attribute === undefined) continue;

					const buffer = attribute.buffer;
					const type = attribute.type;
					const bytesPerElement = attribute.bytesPerElement;

					if (geometryAttribute.isInterleavedBufferAttribute) {
						const data = geometryAttribute.data;
						const stride = data.stride;
						const offset = geometryAttribute.offset;

						if (data && data.isInstancedInterleavedBuffer) {
							for (let i = 0; i < programAttribute.locationSize; i ++) {
								enableAttributeAndDivisor(programAttribute.location + i, data.meshPerAttribute);
							}

							if (object.isInstancedMesh !== true && geometry._maxInstanceCount === undefined) {
								geometry._maxInstanceCount = data.meshPerAttribute * data.count;
							}

						} else {
							for (let i = 0; i < programAttribute.locationSize; i ++) {
								enableAttribute(programAttribute.location + i);
							}
						}

						glBindBuffer(GL_ARRAY_BUFFER, buffer);

						for (let i = 0; i < programAttribute.locationSize; i ++) {
							vertexAttribPointer(
								programAttribute.location + i,
								size / programAttribute.locationSize,
								type,
								normalized,
								stride * bytesPerElement,
								(offset + (size / programAttribute.locationSize) * i) * bytesPerElement
							);
						}
					} else {
						if (geometryAttribute.isInstancedBufferAttribute) {
							for (let i = 0; i < programAttribute.locationSize; i ++) {
								enableAttributeAndDivisor(programAttribute.location + i, geometryAttribute.meshPerAttribute);
							}

							if (object.isInstancedMesh !== true && geometry._maxInstanceCount === undefined) {
								geometry._maxInstanceCount = geometryAttribute.meshPerAttribute * geometryAttribute.count;
							}
						} else {
							for (let i = 0; i < programAttribute.locationSize; i ++) {
								enableAttribute(programAttribute.location + i);
							}
						}

						glBindBuffer(GL_ARRAY_BUFFER, buffer);

						for (let i = 0; i < programAttribute.locationSize; i ++) {
							vertexAttribPointer(
								programAttribute.location + i,
								size / programAttribute.locationSize,
								type,
								normalized,
								size * bytesPerElement,
								(size / programAttribute.locationSize) * i * bytesPerElement
							);
						}
					}
				} else if (materialDefaultAttributeValues !== undefined) {
					const value = materialDefaultAttributeValues[name];
					if (value !== undefined) {
						switch (value.length) {
							case 2:
								gl.vertexAttrib2fv(programAttribute.location, value);
								break;
							case 3:
								gl.vertexAttrib3fv(programAttribute.location, value);
								break;
							case 4:
								gl.vertexAttrib4fv(programAttribute.location, value);
								break;
							default:
								gl.vertexAttrib1fv(programAttribute.location, value);
						}
					}
				}
			}
		}

		disableUnusedAttributes();
	}
};
}