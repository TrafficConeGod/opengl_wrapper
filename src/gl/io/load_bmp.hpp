#pragma once
#include "texture.hpp"
#include "shader_program.hpp"
#include "view.hpp"
#include <string>

namespace gl::io {
    texture load_bmp(shader_program& program, view<byte> image_data);
}