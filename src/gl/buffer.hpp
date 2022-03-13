#pragma once
#include "types.hpp"
#include "view.hpp"

namespace gl {
    template<typename T>
    class buffer {
        gl::uint id;
        public:
            inline buffer() {
                glGenBuffers(1, &id);
            }
            buffer(const buffer&) = delete;
            buffer& operator=(const buffer&) = delete;

            inline void bind() const {
                glBindBuffer(GL_ARRAY_BUFFER, id);
            }

            inline void set_data(gl::view<T> data_view) {
                bind();
                glBufferData(GL_ARRAY_BUFFER, data_view.size() * sizeof(T), data_view.data(), GL_STATIC_DRAW);
            }
    };
}