#pragma once

#include <glad/glad.h>

namespace gl {
class RenderList(properties) {
    const renderItems = [];
    let renderItemsIndex = 0;
    const opaque = [];
    const transmissive = [];
    const transparent = [];
    const defaultProgram = {
        id: -1
    };

    function init() {
        renderItemsIndex = 0;
        opaque.length = 0;
        transmissive.length = 0;
        transparent.length = 0;
    }

    function getNextRenderItem(object, geometry, material, groupOrder, z, group) {
        let renderItem = renderItems[renderItemsIndex];
        const materialProperties = properties.get(material);

        if (renderItem === undefined) {
            renderItem = {
                id: object.id,
                object: object,
                geometry: geometry,
                material: material,
                program: materialProperties.program || defaultProgram,
                groupOrder: groupOrder,
                renderOrder: object.renderOrder,
                z: z,
                group: group
            };
            renderItems[renderItemsIndex] = renderItem;
        } else {
            renderItem.id = object.id;
            renderItem.object = object;
            renderItem.geometry = geometry;
            renderItem.material = material;
            renderItem.program = materialProperties.program || defaultProgram;
            renderItem.groupOrder = groupOrder;
            renderItem.renderOrder = object.renderOrder;
            renderItem.z = z;
            renderItem.group = group;
        }

        renderItemsIndex++;
        return renderItem;
    }

    function push(object, geometry, material, groupOrder, z, group) {
        const renderItem = getNextRenderItem(object, geometry, material, groupOrder, z, group);

        if (material.transmission > 0.0) {
            transmissive.push(renderItem);
        } else if (material.transparent === true) {
            transparent.push(renderItem);
        } else {
            opaque.push(renderItem);
        }
    }

    function unshift(object, geometry, material, groupOrder, z, group) {
        const renderItem = getNextRenderItem(object, geometry, material, groupOrder, z, group);

        if (material.transmission > 0.0) {
            transmissive.unshift(renderItem);
        } else if (material.transparent === true) {
            transparent.unshift(renderItem);
        } else {
            opaque.unshift(renderItem);
        }
    }

    function sort(customOpaqueSort, customTransparentSort) {
        if (opaque.length > 1) opaque.sort(customOpaqueSort || painterSortStable);
        if (transmissive.length > 1) transmissive.sort(customTransparentSort || reversePainterSortStable);
        if (transparent.length > 1) transparent.sort(customTransparentSort || reversePainterSortStable);
    }

    function finish() {
        // Clear references from inactive renderItems in the list
        for (let i = renderItemsIndex, il = renderItems.length; i < il; i++) {
            const renderItem = renderItems[i];
            if (renderItem.id === null) break;
            renderItem.id = null;
            renderItem.object = null;
            renderItem.geometry = null;
            renderItem.material = null;
            renderItem.program = null;
            renderItem.group = null;
        }
    }

    return {
        opaque: opaque,
        transmissive: transmissive,
        transparent: transparent,
        init: init,
        push: push,
        unshift: unshift,
        finish: finish,
        sort: sort
    };
}
}