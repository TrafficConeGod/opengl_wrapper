#include "load_bmp.hpp"
using namespace gl;
#include <stdexcept>
#include "std_ext/interpret_as.hpp"

texture io::load_bmp(shader_program& program, std::ext::view<std::ext::byte> image_data) {
    if (image_data.size() <= 54) {
        throw std::runtime_error("invalid file size");
    }
    if (image_data[0] != 'B' || image_data[1] != 'M') {
        throw std::runtime_error("not a bitmap file");
    }
    if (std::ext::interpret_as<int>(image_data.begin() + 0x1E, image_data.end()) != 3) {
        throw std::runtime_error("not a 24-bit bitmap");
    }
    if (std::ext::interpret_as<char>(image_data.begin() + 0x1C, image_data.end()) != 32) {
        throw std::runtime_error("not a 24-bit bitmap");
    }

    auto data_pos = std::ext::interpret_as<uint>(image_data.begin() + 0x0A, image_data.end());
    auto image_size = std::ext::interpret_as<uint>(image_data.begin() + 0x22, image_data.end());
    auto width = std::ext::interpret_as<uint>(image_data.begin() + 0x12, image_data.end());
    auto height = std::ext::interpret_as<uint>(image_data.begin() + 0x16, image_data.end());

    if (image_size == 0) {
        image_size = width * height * 4;
    }
    if (data_pos == 0) {
        data_pos = 54;
    }

    // auto color_data = std::ext::make_view<std::ext::byte>(image_data.begin() + data_pos, image_data.end());

    // texture texture;
    // texture.bind();


    throw std::runtime_error("not implemented");
}