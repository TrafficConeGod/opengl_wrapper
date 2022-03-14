#pragma once
#include "types.hpp"

namespace gl::enums {
    enum class depth_func : gl::enum_ {
        NEVER = GL_NEVER,
        LESS = GL_LESS,
        EQUAL = GL_EQUAL,
        LEQUAL = GL_LEQUAL,
        GREATER = GL_GREATER,
        NOTEQUAL = GL_NOTEQUAL,
        GEQUAL = GL_GEQUAL,
        ALWAYS = GL_ALWAYS
    };
}