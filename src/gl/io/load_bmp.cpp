#include "load_bmp.hpp"
using namespace gl;
#include <stdexcept>

template<typename T, typename I>
T interpret_as(I begin, I end) {
    if (end - begin != sizeof(T)) {
        throw std::runtime_error("invalid data size");
    }
    return *reinterpret_cast<const T*>(&(*begin));
}

texture io::load_bmp(shader_program& program, view<byte> image_data) {
    if (image_data.size() <= 54) {
        throw std::runtime_error("invalid file size");
    }
    if (image_data[0] != 'B' || image_data[1] != 'M') {
        throw std::runtime_error("not a bitmap file");
    }
    if (interpret_as<int>(image_data.begin() + 0x1E, image_data.end() + 0x1E + sizeof(int)) != 3) {
        throw std::runtime_error("not a 24-bit bitmap");
    }
    if (interpret_as<char>(image_data.begin() + 0x1C, image_data.end() + 0x1C + sizeof(char)) != 32) {
        throw std::runtime_error("not a 24-bit bitmap");
    }

    auto data_pos = interpret_as<uint>(image_data.begin() + 0x0A, image_data.begin() + 0x0A + sizeof(uint));
    auto image_size = interpret_as<uint>(image_data.begin() + 0x22, image_data.begin() + 0x22 + sizeof(uint));
    auto width = interpret_as<uint>(image_data.begin() + 0x12, image_data.begin() + 0x12 + sizeof(uint));
    auto height = interpret_as<uint>(image_data.begin() + 0x16, image_data.begin() + 0x16 + sizeof(uint));

    if (image_size == 0) {
        image_size = width * height * 4;
    }
    if (data_pos == 0) {
        data_pos = 54;
    }

    // auto color_data = make_view<byte>(image_data.begin() + data_pos, image_data.end());

    // texture texture;
    // texture.bind();


    throw std::runtime_error("not implemented");
}