#pragma once
#include "types.hpp"

namespace gl::enums {
    enum class image_format : gl::enum_ {
        RED = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        BGR = GL_BGR,
        RGBA = GL_RGBA,
        BGRA = GL_BGRA,
        //
        STENCIL_INDEX = GL_STENCIL_INDEX,
        DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
        DEPTH_STENCIL = GL_DEPTH_STENCIL
    };
}