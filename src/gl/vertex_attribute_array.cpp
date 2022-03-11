#include "vertex_attribute_array.hpp"
using namespace gl;

void vertex_attribute_array::set_data(const buffer& buf, const std::vector<float>& data) {
    buf.bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * 4, data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(layout_position, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}