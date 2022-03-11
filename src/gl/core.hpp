#pragma once
#include "enums/general.hpp"
#include "enums/toggle.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <initializer_list>

namespace gl {
    inline void enable(enums::toggle toggle) {
        glEnable((GLenum)toggle);
    }
    inline void set_depth_func(enums::general func) {
        glDepthFunc((GLenum)func);
    }
    inline void set_blend_func(enums::general src, enums::general dst) {
        glBlendFunc((GLenum)src, (GLenum)dst);
    }
    inline void set_clear_color(glm::vec3 color) {
        glClearColor(color.r, color.g, color.b, 0.0f);
    }
    inline void set_clear_color(glm::vec4 color) {
        glClearColor(color.a, color.r, color.g, color.w);
    }
    
    inline void gen_vertex_arrays() {
        GLuint vertex_array_id;
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);
    }

    inline void clear_frame(std::initializer_list<enums::general> options) {
        GLbitfield mask = 0;
        for (auto option : options) {
            mask |= (GLbitfield)option;
        }
        glClear(mask);
    }
}