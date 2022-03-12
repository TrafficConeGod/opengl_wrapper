#include "load_bmp.hpp"
using namespace gl;

template<typename T, typename I>
T interpret_as(I begin, I end) {
    if (end - begin != sizeof(T)) {
        throw std::runtime_error("invalid data size");
    }
    return *reinterpret_cast<const T*>(&(*begin));
}

// texture io::load_bmp(view<byte> image_data) {
//     view<byte> header(image_data.begin(), image_data.begin() + 54);
//     auto data_pos = interpret_as<uint>(header.begin() + 0x0A, header.begin() + 0x0A + sizeof(uint));
// }