#pragma once
#include "buffer.hpp"
#include <vector>

namespace gl {
    class vertex_attribute_array {
        gl::uint layout_position;

        template<typename T>
        inline void set_vertex_attrib_pointer(gl::uint dim) = delete;

        public:
            inline vertex_attribute_array(gl::uint layout_position) : layout_position(layout_position) {
                glEnableVertexAttribArray(layout_position);
            }
            inline ~vertex_attribute_array() {
                glDisableVertexAttribArray(layout_position);
            }
            vertex_attribute_array(const vertex_attribute_array&) = delete;
            vertex_attribute_array& operator=(const vertex_attribute_array&) = delete;

            template<typename Underlying_Data_Type, typename High_Level_Data_Type>
            void set_data(gl::uint dim, const buffer& buf, const std::vector<High_Level_Data_Type>& data) {
                buf.bind();
                glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(High_Level_Data_Type), data.data(), GL_STATIC_DRAW);
                set_vertex_attrib_pointer<Underlying_Data_Type>(dim);
            }
    };
}

template<>
inline void gl::vertex_attribute_array::set_vertex_attrib_pointer<float>(gl::uint dim) {
    glVertexAttribPointer(layout_position, dim, GL_FLOAT, GL_FALSE, 0, 0);
}