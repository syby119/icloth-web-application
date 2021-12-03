#include "binding_states.h"

BindingStates::BindingStates(AttributeManager& attributes) {
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes);
}

void BindingStates::setup(Object3D* object, material, program, geometry, index) {
    bool updateBuffers = false;

    const state = getBindingState(geometry, program, material);
    if (currentState !== state) {
        currentState = state;
        glBindVertexArray(currentState.object);
    }

    updateBuffers = needsUpdate(geometry, index);
    if (updateBuffers) {
        saveCache(geometry, index);
    }

    if (index !== null) {
        attributes.update(index, GL_ELEMENT_ARRAY_BUFFER);
    }

    if (updateBuffers) {
        setupVertexAttributes(object, material, program, geometry);
        if (index !== null) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, attributes.get(index).buffer);
        }
    }
}

void BindingStates::reset() {
    resetDefaultState();
    if (currentState == defaultState) return;

    currentState = defaultState;
    glBindVertexArray(currentState.object);
}

void BindingStates::resetDefaultState() {
    defaultState.geometry = null;
    defaultState.program = null;
    defaultState.wireframe = false;
}

void BindingStates::dispose() {
    reset();

    for (const geometryId in bindingStates) {
        const programMap = bindingStates[geometryId];
        for (const programId in programMap) {
            const stateMap = programMap[programId];
            for (const wireframe in stateMap) {
                glDeleteVertexArrays(stateMap[wireframe].object);
                delete stateMap[wireframe];
            }
            delete programMap[programId];
        }
        delete bindingStates[geometryId];
    }
}

void BindingStates::releaseStatesOfGeometry(geometry) {
    if (bindingStates[geometry.id] === undefined) return;
    const programMap = bindingStates[geometry.id];

    for (const programId in programMap) {
        const stateMap = programMap[programId];
        for (const wireframe in stateMap) {
            glDeleteVertexArrays(stateMap[wireframe].object);
            delete stateMap[wireframe];
        }

        delete programMap[programId];
    }

    delete bindingStates[geometry.id];
}

void BindingStates::releaseStatesOfProgram(program) {
    for (const geometryId in bindingStates) {
        const programMap = bindingStates[geometryId];
        if (programMap[program.id] === undefined) continue;
        const stateMap = programMap[program.id];
        for (const wireframe in stateMap) {
            glDeleteVertexArrays(stateMap[wireframe].object);
            delete stateMap[wireframe];
        }

        delete programMap[program.id];
    }
}

void BindingStates::initAttributes() {
    const newAttributes = currentState.newAttributes;
    for (let i = 0, il = newAttributes.length; i < il; i ++) {
        newAttributes[i] = 0;
    }
}

void BindingStates::enableAttribute(attribute);

void BindingStates::disableUnusedAttributes() {
    const newAttributes = currentState.newAttributes;
    const enabledAttributes = currentState.enabledAttributes;

    for (let i = 0, il = enabledAttributes.length; i < il; i ++) {
        if (enabledAttributes[i] !== newAttributes[i]) {
            glDisableVertexAttribArray(i);
            enabledAttributes[i] = 0;
        }
    }
}