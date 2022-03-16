#pragma once
#include "enums/toggle.hpp"
#include "enums/clear_frame_option.hpp"
#include "enums/depth_func.hpp"
#include "enums/blend_func.hpp"
#include "enums/draw_mode.hpp"
#include "buffer.hpp"
#include "std_ext/view.hpp"
#include "types.hpp"
#include <glm/glm.hpp>
#include <initializer_list>

namespace gl {
    inline void enable(enums::toggle toggle) {
        glEnable((gl::enum_)toggle);
    }
    inline void set_depth_func(enums::depth_func func) {
        glDepthFunc((gl::enum_)func);
    }
    inline void set_blend_func(enums::blend_func src, enums::blend_func dst) {
        glBlendFunc((gl::enum_)src, (gl::enum_)dst);
    }
    inline void set_clear_color(glm::vec3 color) {
        glClearColor(color.r, color.g, color.b, 0.0f);
    }
    inline void set_clear_color(glm::vec4 color) {
        glClearColor(color.a, color.r, color.g, color.w);
    }
    
    inline void gen_vertex_arrays(std::size_t count) {
        gl::uint vertex_array_id;
        glGenVertexArrays(count, &vertex_array_id);
        glBindVertexArray(vertex_array_id);
    }

    inline void clear_frame(std::initializer_list<enums::clear_frame_option> options) {
        gl::bit_field mask = 0;
        for (auto option : options) {
            mask |= (gl::bit_field)option;
        }
        glClear(mask);
    }

    inline void draw_arrays(enums::draw_mode mode, gl::size_t count) {
        glDrawArrays((gl::enum_)mode, 0, count);
    }

    inline void draw_elements(enums::draw_mode mode, std::ext::view<gl::uint> indices) {
        glDrawElements((gl::enum_)mode, indices.size() * sizeof(gl::uint), GL_UNSIGNED_INT, indices.data());
    }
}