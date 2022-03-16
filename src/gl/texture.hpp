#pragma once
#include "types.hpp"
#include "std_ext/view.hpp"
#include "enums/image_format.hpp"
#include "enums/compressed_image_format.hpp"
#include "enums/general.hpp"
#include <stdexcept>

namespace gl {
    class texture {
        gl::uint id;
        u_char current_slot;
        public:
            struct mipmap {
                enums::image_format internal_format;
                gl::size_t width;
                gl::size_t height;
                enums::image_format input_format;
                std::ext::view<gl::ubyte> data;
            };
            struct compressed_mipmap {
                enums::compressed_image_format internal_format;
                gl::size_t width;
                gl::size_t height;
                std::ext::view<gl::ubyte> data;
            };

            struct param {
                enums::general type;
                enums::general value;
            };
    
            texture(u_char slot_, std::ext::view<param> params, std::ext::view<mipmap> mipmaps);
            texture(u_char slot_, std::ext::view<param> params, std::ext::view<compressed_mipmap> mipmaps, gl::int_ unpack_alignment);
            texture(const texture&) = delete;
            texture& operator=(const texture&) = delete;

            inline void bind() const {
                glBindTexture(GL_TEXTURE_2D, id);
            }

            [[nodiscard]] inline u_char slot() const {
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