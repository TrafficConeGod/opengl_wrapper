#include "texture.hpp"
using namespace gl;

void texture::init_params(const parameters& params) {
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, (gl::enum_)params.depth_stencil_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, params.base_level);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (gl::enum_)params.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (gl::enum_)params.mag_filter);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, params.min_lod);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, params.max_lod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, params.max_level);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, (gl::enum_)params.swizzle_r);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, (gl::enum_)params.swizzle_g);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, (gl::enum_)params.swizzle_b);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, (gl::enum_)params.swizzle_a);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (gl::enum_)params.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (gl::enum_)params.wrap_t);
}

texture::texture(u_char slot_, const parameters& params, std::ext::view<mipmap> mipmaps) {
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

    init_params(params);

    glGenerateMipmap(GL_TEXTURE_2D);
}

texture::texture(u_char slot_, const parameters& params, std::ext::view<compressed_mipmap> mipmaps) {
    slot(slot_);

    glGenTextures(1, &id);

    bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

    init_params(params);
}