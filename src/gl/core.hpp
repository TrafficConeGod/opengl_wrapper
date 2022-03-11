#pragma once
#include "enums/general.hpp"
#include "enums/toggle.hpp"
#include <GL/glew.h>

namespace gl {
    inline void enable(enums::toggle toggle) {
        glEnable((GLenum)toggle);
    }
    void set_depth_func(enums::general func);
    void set_blend_func(enums::general src, enums::general dst);
}