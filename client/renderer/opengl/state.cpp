#include "state.h"

namespace gl {

State::State() {
    glGetParameter();

    emptyTextures();
    
    assert(0);
}

void activeTexture(GLenum slot) {
    if (!slot) {
        slot = GL_TEXTURE0 + maxTextures - 1;
    }

    if (currentTextureSlot != slot) {
        glActiveTexture(slot);
        currentTextureSlot = slot;
    }
}




}