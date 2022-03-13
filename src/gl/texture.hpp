#pragma once
#include "types.hpp"

namespace gl {
    class texture {
        gl::uint id;
        public:
            inline texture() {
                glGenTextures(1, &id);
            }
            texture(const texture&) = delete;
            texture& operator=(const texture&) = delete;

            inline texture(texture&& other) : id(other.id) { other.id = -1; }

            inline void bind() const {
                glBindTexture(GL_TEXTURE_2D, id);
            }
    };
}