#pragma once
#include "types.hpp"
#include <string>

namespace gl {
    class shader_program {
        gl::uint id;
        public:
            shader_program(std::string_view vert_shader_source, std::string_view frag_shader_source);
            shader_program(const shader_program&) = delete;
            shader_program& operator=(const shader_program&) = delete;

            inline void use() {
                glUseProgram(id);
            }
    };
}