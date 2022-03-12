#pragma once
#include "types.hpp"
#include "view.hpp"

namespace gl {
    class buffer_object {
        gl::uint id;
        public:
            inline buffer_object() {
                glGenBuffers(1, &id);
            }
            buffer_object(const buffer_object&) = delete;
            buffer_object& operator=(const buffer_object&) = delete;

            inline void bind() const {
                glBindBuffer(GL_ARRAY_BUFFER, id);
            }

            template<typename T>
            inline void set_data(gl::view<T> data_view) {
                bind();
                glBufferData(GL_ARRAY_BUFFER, data_view.size() * sizeof(T), data_view.data(), GL_STATIC_DRAW);
            }
    };
}