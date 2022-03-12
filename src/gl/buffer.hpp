#pragma once
#include "types.hpp"

namespace gl {
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
    };
}