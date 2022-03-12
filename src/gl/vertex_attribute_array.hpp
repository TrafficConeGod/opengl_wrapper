#pragma once
#include "buffer_object.hpp"
#include "view.hpp"

namespace gl {
    template<typename T>
    inline void set_vertex_attrib_pointer(gl::uint layout_position, gl::uint dim) = delete;

    template<>
    inline void set_vertex_attrib_pointer<float>(gl::uint layout_position, gl::uint dim) {
        glVertexAttribPointer(layout_position, dim, GL_FLOAT, GL_FALSE, 0, 0);
    }

    template<typename T>
    class vertex_attribute_array {
        gl::uint layout_position;

        public:
            inline vertex_attribute_array(gl::uint layout_position, gl::uint dim, const buffer_object& buf_obj) : layout_position(layout_position) {
                glEnableVertexAttribArray(layout_position);
                buf_obj.bind();
                set_vertex_attrib_pointer<T>(layout_position, dim);
            }
            inline ~vertex_attribute_array() {
                glDisableVertexAttribArray(layout_position);
            }
            vertex_attribute_array(const vertex_attribute_array&) = delete;
            vertex_attribute_array& operator=(const vertex_attribute_array&) = delete;
    };
}