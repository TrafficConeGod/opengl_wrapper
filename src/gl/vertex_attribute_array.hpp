#pragma once
#include "buffer.hpp"
#include <vector>

namespace gl {
    class vertex_attribute_array {
        GLuint layout_position;
        public:
            inline vertex_attribute_array(GLuint layout_position) {
                glEnableVertexAttribArray(layout_position);
            }
            inline ~vertex_attribute_array() {
                glDisableVertexAttribArray(layout_position);
            }
            vertex_attribute_array(const vertex_attribute_array&) = delete;
            vertex_attribute_array& operator=(const vertex_attribute_array&) = delete;

            void set_data(const buffer& buf, const std::vector<float>& data);
    };
}