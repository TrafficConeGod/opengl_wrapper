#pragma once
#include "types.hpp"
#include "get_type_enum.hpp"

namespace gl {
    inline void set_vertex_attrib_pointer(gl::uint index, gl::uint dim, gl::enum_ type, gl::size_t stride, const void* pointer) {
        glVertexAttribPointer(index, dim, type, GL_FALSE, stride, pointer);
    }

    template<typename T>
    struct get_set_vertex_attrib_pointer_function {};

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::byte> {
        static constexpr auto value = &glVertexAttribIPointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::float_> {
        static constexpr auto value = &set_vertex_attrib_pointer;
    };
};