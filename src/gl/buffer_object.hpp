#pragma once
#include "types.hpp"

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
    };
}