#pragma once
#include "types.hpp"

namespace gl::enums {
    enum class clear_frame_option : gl::bit_field {
        COLOR = GL_COLOR_BUFFER_BIT,
        DEPTH = GL_DEPTH_BUFFER_BIT,
        STENCIL = GL_STENCIL_BUFFER_BIT
    };
}