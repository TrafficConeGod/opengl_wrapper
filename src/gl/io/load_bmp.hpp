#pragma once
#include "texture.hpp"
#include "view.hpp"
#include <string>

namespace gl::io {
    texture load_bmp(view<byte> image_data);
}