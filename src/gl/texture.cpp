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
            (gl::int_)mipmap.internal_format,
            mipmap.width,
            mipmap.height,
            0,
            (gl::enum_)mipmap.input_format,
            GL_UNSIGNED_BYTE,
            mipmap.data.data()
        );
        level++;
    }

    for (auto& param : params) {
        glTexParameteri(GL_TEXTURE_2D, (gl::enum_)param.type, (gl::int_)param.value);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
}

texture::texture(u_char slot_, std::ext::view<param> params, std::ext::view<compressed_mipmap> mipmaps, gl::int_ unpack_alignment) {
    slot(slot_);

    glGenTextures(1, &id);

    bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment);

    std::size_t level = 0;
    for (auto& mipmap : mipmaps) {
        glCompressedTexImage2D(
            GL_TEXTURE_2D,
            level,
            (gl::enum_)mipmap.internal_format,
            mipmap.width,
            mipmap.height,
			0,
            mipmap.data.size(),
            mipmap.data.data()
        );
        level++;
    }

    for (auto& param : params) {
        glTexParameteri(GL_TEXTURE_2D, (gl::enum_)param.type, (gl::int_)param.value);
    }
}