#pragma once
#include "types.hpp"

namespace gl::enums {
    enum class clear_frame_option : gl::bit_field {
        COLOR = 0x00004000,
        DEPTH = 0x00000100,
        STENCIL = 0x00000400,
    };
}