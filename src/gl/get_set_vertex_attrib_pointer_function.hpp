#pragma once
#include "types.hpp"
#include "get_type_enum.hpp"

namespace gl {
    inline void set_vertex_attrib_pointer(gl::uint index, gl::uint dim, gl::enum_ type, gl::size_t stride, const void* pointer) {
        glVertexAttribPointer(index, dim, type, GL_FALSE, stride, pointer);
    }

    inline void set_vertex_attrib_int_pointer(gl::uint index, gl::uint dim, gl::enum_ type, gl::size_t stride, const void* pointer) {
        glVertexAttribIPointer(index, dim, type, stride, pointer);
    }

    template<typename T>
    struct get_set_vertex_attrib_pointer_function {};

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::byte> {
        static constexpr auto value = &set_vertex_attrib_int_pointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::ubyte> {
        static constexpr auto value = &set_vertex_attrib_int_pointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::short_> {
        static constexpr auto value = &set_vertex_attrib_int_pointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::ushort_> {
        static constexpr auto value = &set_vertex_attrib_int_pointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::int_> {
        static constexpr auto value = &set_vertex_attrib_int_pointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::uint> {
        static constexpr auto value = &set_vertex_attrib_int_pointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::float_> {
        static constexpr auto value = &set_vertex_attrib_pointer;
    };

    template<>
    struct get_set_vertex_attrib_pointer_function<gl::double_> {
        static constexpr auto value = &set_vertex_attrib_pointer;
    };
};