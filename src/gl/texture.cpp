#include "texture.hpp"
using namespace gl;

texture::texture(u_char slot_, std::ext::view<param> params, std::ext::view<mipmap> mipmaps) {
    slot(slot_);

    glGenTextures(1, &id);

    bind();

    std::size_t level = 0;
    for (auto& mipmap : mipmaps) {
        glTexImage2D(
            GL_TEXTURE_2D,
            level,
            (GLint)mipmap.internal_format,
            mipmap.width,
            mipmap.height,
            0,
            (GLenum)mipmap.input_format,
            GL_UNSIGNED_BYTE,
            mipmap.data.data()
        );
        level++;
    }

    for (auto& param : params) {
        glTexParameteri(GL_TEXTURE_2D, (GLenum)param.type, (GLint)param.value);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
}