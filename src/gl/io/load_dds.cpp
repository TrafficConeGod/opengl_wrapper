#include "io.hpp"
using namespace gl;
#include "std_ext/interpret_as.hpp"
#include <vector>

enum class four_cc : uint {
    DXT1 = 0x31545844,
    DXT3 = 0x33545844,
    DXT5 = 0x35545844
};

gl::texture io::load_dds(u_char slot, std::ext::view<gl::texture::param> params, std::ext::view<std::ext::byte> image_data) {
    if (image_data[0] != 'D' || image_data[1] != 'D' || image_data[2] != 'S' || image_data[3] != ' ') {
        throw std::runtime_error("not a dds file");
    }
    const auto header = image_data.begin() + 4;
    auto height = std::ext::interpret_as<uint>(header + 8, image_data.end());
    auto width = std::ext::interpret_as<uint>(header + 12, image_data.end());
    const auto mip_map_count = std::ext::interpret_as<uint>(header + 24, image_data.end());
    const auto four_cc_type = std::ext::interpret_as<four_cc>(header + 80, image_data.end());

    enums::compressed_image_format format;
    switch (four_cc_type) { 
		case four_cc::DXT1: 
			format = enums::compressed_image_format::RGBA_S3TC_DXT1_EXT; 
			break; 
		case four_cc::DXT3: 
			format = enums::compressed_image_format::RGBA_S3TC_DXT3_EXT; 
			break; 
		case four_cc::DXT5: 
			format = enums::compressed_image_format::RGBA_S3TC_DXT5_EXT; 
			break; 
		default: 
			throw std::runtime_error("unsupported format");
	}
    const auto block_size = (format == enums::compressed_image_format::RGBA_S3TC_DXT1_EXT) ? 8 : 16;

    std::vector<gl::texture::compressed_mipmap> mipmaps;

    auto data_it = image_data.begin() + 128;
    for (std::size_t i = 0; i < mip_map_count; ++i) {
        uint size = ((width+3)/4)*((height+3)/4)*block_size;
        mipmaps.push_back({
            .internal_format = format,
            .width = (gl::size_t)width,
            .height = (gl::size_t)height,
            .data = {data_it, data_it + size}
        });
        data_it += size;

        width /= 2;
        height /= 2;

        if (width < 1) {
            width = 1;
        }
		if (height < 1) {
            height = 1;
        }
    }

    return {
        slot,
        params,
        std::ext::view<gl::texture::compressed_mipmap>(mipmaps)
    };
}