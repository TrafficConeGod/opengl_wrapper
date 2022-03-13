#pragma once
#include "texture.hpp"
#include "shader_program.hpp"
#include "std_ext/byte.hpp"
#include "std_ext/view.hpp"
#include <string>

namespace gl::io {
    texture load_bmp(std::ext::view<std::ext::byte> image_data);
}