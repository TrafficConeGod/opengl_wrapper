#pragma once
#include "types.hpp"
#include "std_ext/view.hpp"
#include <stdexcept>

namespace gl {
    class texture {
        gl::uint id;
        u_char current_slot;
        public:
            texture(u_char slot_, gl::uint width, gl::uint height, std::ext::view<gl::ubyte> data);
            texture(const texture&) = delete;
            texture& operator=(const texture&) = delete;

            inline void bind() const {
                glBindTexture(GL_TEXTURE_2D, id);
            }

            inline u_char slot() const {
                if (current_slot == 0xff) {
                    throw std::runtime_error("texture not in slot");
                }
                return current_slot;
            }

            inline void slot(u_char slot) {
                if (slot >= 32) {
                    throw std::runtime_error("slot is out of range");
                }
                current_slot = slot;
            }
    };
}