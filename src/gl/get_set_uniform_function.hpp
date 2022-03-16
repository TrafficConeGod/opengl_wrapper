#pragma once
#include "types.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>

namespace gl {
    template<typename T>
    struct get_set_uniform_function {};

    inline void set_uniform_1f(gl::uint id, void* value) {
        glUniform1fv(id, 1, (gl::float_*)value);
    }

    inline void set_uniform_1i(gl::uint id, void* value) {
        glUniform1iv(id, 1, (gl::int_*)value);
    }

    inline void set_uniform_1ui(gl::uint id, void* value) {
        glUniform1uiv(id, 1, (gl::uint*)value);
    }

    inline void set_uniform_2f(gl::uint id, void* value) {
        glUniform2fv(id, 1, (gl::float_*)value);
    }

    inline void set_uniform_2i(gl::uint id, void* value) {
        glUniform2iv(id, 1, (gl::int_*)value);
    }

    inline void set_uniform_2ui(gl::uint id, void* value) {
        glUniform2uiv(id, 1, (gl::uint*)value);
    }

    inline void set_uniform_3f(gl::uint id, void* value) {
        glUniform3fv(id, 1, (gl::float_*)value);
    }

    inline void set_uniform_3i(gl::uint id, void* value) {
        glUniform3iv(id, 1, (gl::int_*)value);
    }

    inline void set_uniform_3ui(gl::uint id, void* value) {
        glUniform3uiv(id, 1, (gl::uint*)value);
    }

    inline void set_uniform_4f(gl::uint id, void* value) {
        glUniform4fv(id, 1, (gl::float_*)value);
    }

    inline void set_uniform_4i(gl::uint id, void* value) {
        glUniform4iv(id, 1, (gl::int_*)value);
    }

    inline void set_uniform_4ui(gl::uint id, void* value) {
        glUniform4uiv(id, 1, (gl::uint*)value);
    }

    template<>
    struct get_set_uniform_function<gl::float_> {
        constexpr static auto value = &set_uniform_1f;
    };

    template<>
    struct get_set_uniform_function<gl::int_> {
        constexpr static auto value = &set_uniform_1i;
    };

    template<>
    struct get_set_uniform_function<gl::uint> {
        constexpr static auto value = &set_uniform_1i;
    };

    template<>
    struct get_set_uniform_function<glm::vec1> {
        constexpr static auto value = &set_uniform_1f;
    };

    template<>
    struct get_set_uniform_function<glm::vec2> {
        constexpr static auto value = &set_uniform_2f;
    };

    template<>
    struct get_set_uniform_function<glm::vec3> {
        constexpr static auto value = &set_uniform_3f;
    };

    template<>
    struct get_set_uniform_function<glm::vec4> {
        constexpr static auto value = &set_uniform_4f;
    };

    template<>
    struct get_set_uniform_function<gl::texture&> {
        static inline void value(gl::uint id, gl::texture* tex) {
            auto slot = tex->slot();
            glActiveTexture(GL_TEXTURE0 + slot);
            tex->bind();
            glUniform1i(id, slot);
        }
    };
};