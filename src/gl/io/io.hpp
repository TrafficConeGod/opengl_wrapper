#pragma once
#include "texture.hpp"
#include "shader_program.hpp"
#include "std_ext/byte.hpp"
#include "std_ext/view.hpp"
#include <string>

namespace gl::io {
    [[nodiscard]] texture load_bmp(u_char slot, std::ext::view<gl::texture::param> params, std::ext::view<std::ext::byte> image_data);
    [[nodiscard]] texture load_dds(u_char slot, std::ext::view<gl::texture::param> params, std::ext::view<std::ext::byte> image_data);
}