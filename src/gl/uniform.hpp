#pragma once
#include "types.hpp"
#include "shader_program.hpp"
#include "texture.hpp"
#include <string>
#include <glm/glm.hpp>

namespace gl {
    class texture;

    template<typename T>
    inline void set_uniform(gl::uint id, T value) = delete;

    template<>
    inline void set_uniform<float>(gl::uint id, float value) {
        glUniform1f(id, value);
    };

    template<>
    inline void set_uniform<glm::vec2>(gl::uint id, glm::vec2 value) {
        glUniform2f(id, value.x, value.y);
    };

    template<>
    inline void set_uniform<gl::texture&>(gl::uint id, gl::texture& value) {
        glActiveTexture(GL_TEXTURE0);
        value.bind();
        glUniform1i(id, 0);
    }

    template<typename T>
    class uniform {
        gl::uint id;
        public:
            inline uniform(shader_program& program, std::string_view name) : id(glGetUniformLocation(program.get_id(), name.data())) {}
            uniform(const uniform&) = delete;
            uniform& operator=(const uniform&) = delete;

            inline void set(T value) {
                set_uniform<T>(id, value);
            }
    };
}