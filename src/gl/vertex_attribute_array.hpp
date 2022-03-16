#pragma once
#include "buffer.hpp"
#include "get_type_enum.hpp"
#include "get_set_vertex_attrib_pointer_function.hpp"

namespace gl {
    template<typename T>
    class vertex_attribute_array {
        gl::uint layout_position;

        public:
            inline vertex_attribute_array(gl::uint layout_position, gl::uint dim) : layout_position(layout_position) {
                glEnableVertexAttribArray(layout_position);
                get_set_vertex_attrib_pointer_function<T>::value(layout_position, dim, (gl::enum_)get_type_enum<T>::value, 0, 0);
            }
            template<typename B>
            inline vertex_attribute_array(gl::uint layout_position, gl::uint dim, const buffer<B>& buf_obj) : layout_position(layout_position) {
                buf_obj.bind();
                glEnableVertexAttribArray(layout_position);
                get_set_vertex_attrib_pointer_function<T>::value(layout_position, dim, (gl::enum_)get_type_enum<T>::value, 0, 0);
            }
            inline ~vertex_attribute_array() {
                glDisableVertexAttribArray(layout_position);
            }
            vertex_attribute_array(const vertex_attribute_array&) = delete;
            vertex_attribute_array& operator=(const vertex_attribute_array&) = delete;
    };
}