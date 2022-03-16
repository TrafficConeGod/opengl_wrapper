#pragma once
#include "types.hpp"
#include "shader_program.hpp"
#include "get_set_uniform_function.hpp"
#include <string>
#include <glm/glm.hpp>

namespace gl {
    template<typename T>
    class uniform {
        gl::uint id;
        public:
            inline uniform(shader_program& program, std::string_view name) : id(glGetUniformLocation(program.get_id(), name.data())) {}
            uniform(const uniform&) = delete;
            uniform& operator=(const uniform&) = delete;

            inline void set(T value) {
                get_set_uniform_function<T>::value(id, &value);
            }
    };
}