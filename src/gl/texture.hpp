#pragma once
#include "types.hpp"
#include "std_ext/view.hpp"
#include "enums/image_format.hpp"
#include "enums/compressed_image_format.hpp"
#include "enums/minify_filter_func.hpp"
#include "enums/magnify_filter_func.hpp"
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

            struct parameters {
                enums::general depth_stencil_mode = enums::general::DEPTH_COMPONENT;
                gl::int_ base_level = 0;
                enums::minify_filter_func min_filter = enums::minify_filter_func::NEAREST_MIPMAP_LINEAR;
                enums::magnify_filter_func mag_filter = enums::magnify_filter_func::LINEAR;
                gl::float_ min_lod = -1000;
                gl::float_ max_lod = 1000;
                gl::int_ max_level = 1000;
                enums::general swizzle_r = enums::general::RED;
                enums::general swizzle_g = enums::general::GREEN;
                enums::general swizzle_b = enums::general::BLUE;
                enums::general swizzle_a = enums::general::ALPHA;
                enums::general wrap_s = enums::general::REPEAT;
                enums::general wrap_t = enums::general::REPEAT;
            };
            
            texture(u_char slot_, const parameters& params, std::ext::view<mipmap> mipmaps);
            texture(u_char slot_, const parameters& params, std::ext::view<compressed_mipmap> mipmaps);
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
        private:
            void init_params(const parameters& params);
    };
}