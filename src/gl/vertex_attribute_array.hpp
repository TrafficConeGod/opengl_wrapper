#pragma once
#include "buffer.hpp"
#include <vector>

namespace gl {
    class vertex_attribute_array {
        GLuint layout_position;

        template<typename T>
        inline void set_vertex_attrib_pointer(GLuint dim) = delete;

        public:
            inline vertex_attribute_array(GLuint layout_position) : layout_position(layout_position) {
                glEnableVertexAttribArray(layout_position);
            }
            inline ~vertex_attribute_array() {
                glDisableVertexAttribArray(layout_position);
            }
            vertex_attribute_array(const vertex_attribute_array&) = delete;
            vertex_attribute_array& operator=(const vertex_attribute_array&) = delete;

            template<GLuint dim, typename UnderlyingDataType, typename HighLevelDataType>
            void set_data(const buffer& buf, const std::vector<HighLevelDataType>& data) {
                buf.bind();
                glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(HighLevelDataType), data.data(), GL_STATIC_DRAW);
                set_vertex_attrib_pointer<UnderlyingDataType>(dim);
            }
    };
}

template<>
inline void gl::vertex_attribute_array::set_vertex_attrib_pointer<float>(GLuint dim) {
    glVertexAttribPointer(layout_position, dim, GL_FLOAT, GL_FALSE, 0, 0);
}