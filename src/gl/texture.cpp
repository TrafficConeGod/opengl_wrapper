#include "texture.hpp"
using namespace gl;

texture::texture(u_char slot_, std::ext::view<mipmap> mipmaps) {
    slot(slot_);

    glGenTextures(1, &id);

    bind();

    for (auto& mipmap : mipmaps) {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            (GLint)mipmap.internal_format,
            mipmap.width,
            mipmap.height,
            0,
            (GLenum)mipmap.input_format,
            GL_UNSIGNED_BYTE,
            mipmap.data.data()
        );
    }

    // Nice filtering, or ...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

    // ... ugly trilinear filtering ...
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // ... which requires mipmaps. Generate them automatically.
    glGenerateMipmap(GL_TEXTURE_2D);
}