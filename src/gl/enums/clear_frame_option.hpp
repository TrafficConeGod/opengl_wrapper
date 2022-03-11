#pragma once
#include <GL/glew.h>

namespace gl::enums {
    enum class clear_frame_option : GLbitfield {
        COLOR = 0x00004000,
        DEPTH = 0x00000100,
        STENCIL = 0x00000400,
    };
}