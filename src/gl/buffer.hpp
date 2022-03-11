#pragma once
#include <GL/glew.h>

namespace gl {
    class buffer {
        GLuint id;
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