#pragma once
#include "types.hpp"

namespace gl::enums {
    enum class compressed_image_format : gl::enum_ {
        RGB_S3TC_DXT1_EXT = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
        RGBA_S3TC_DXT1_EXT = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
        RGBA_S3TC_DXT3_EXT = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
        RGBA_S3TC_DXT5_EXT = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
    };
}